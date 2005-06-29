////////////////////////////////////////////////////////////////////////////////
//
//	Module:		linux.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	06-19-2005
//	Editors:	Tom Hicks
//
//	Purpose:
//		To implement the OpenArena SDK.
//
//	Summary of Methods:
//	Global
//		-InitControls()
//			Loads the defaultPlayer's configuration.
//		-InitGL()
//			Initializes OpenGL and is responsible for loading textures.
//		-ResizeGLScene(GLsizei width, GLsizei height)
//			Resizes the viewport to the current size of the visible area of the window specified by width and height.
//		-KillGLWindow()
//			Closes the window.
//		-CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag)
//			Creates the window with the specified parameters.
//		-WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//			Main procedure.
//		-WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//			Window Procedure for the OpenGL window.
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __linux

//include necessary header files
#include "../include/main.h"
#include "../include/version.h"
using namespace std;

void InitControls();
unsigned char TranslateKey(int keyCode);
unsigned char TranslateButton(int keyCode);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions

void ResizeGLScene(GLsizei width, GLsizei height)
{
	if(height == 0)
		height = 1;

	glViewport(0,0,width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width/height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

int DrawGLScene()
{
	level.Render();

	g_Screen.SwapBuffers();
	
	return true;
}

//
//void InitControls()
//  Purpose:
//	    Initializes controls by loading the default control config file "my.cfg".
void InitControls()
{
	if (!level.LoadConfig("my.cfg"))
		level.LoadConfig();
}

//
//int InitGL(GLvoid)
//	Purpose:
//		To do all required setup before creating an OpenGL window
int InitGL(GLvoid)
{
	level.LoadGLTextures();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/*lighting disabled temporarily
	glLightfv(GL_LIGHT1, GL_AMBIENT, level.LightAmbient);
	for(index=0; index<level.numLights; index++)
	{
	glLightfv(GL_LIGHT1, GL_DIFFUSE, level.light[index].color);
	glLightfv(GL_LIGHT1, GL_POSITION, level.light[index].coords);
	}

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	*/
	//BuildFont();
	return true;
}

int main(int argc, char** argv)
{
	XEvent event;
	bool done = false;

	string commandLine = "";
	int i;
	for(i=1; i<argc; i++)
	{
		commandLine = commandLine + " " + argv[i];
	}
	level.ParseCmds(commandLine.c_str());

	InitControls();

	level.glFont.SetScreenDimensions(level.screen.width*2, level.screen.height*2);

	if(level.nextLevel == "")
	{
		level.LoadMap("intro.map");
	}
	else
	{
		level.LoadMap();
	}

	//Hack for now
	if(level.screen.bpp == 32)
	{
		level.screen.bpp = 24;
	}

	g_Screen.SetOnInit(InitGL);
	g_Screen.SetOnResize(ResizeGLScene);

	if(!g_Screen.Open(OPENARENA_VERSION, level.screen.width, level.screen.height, level.screen.bpp, level.screen.fullscreen))
	{
		return 1;
	}

	while(!done)
	{
		while(XPending(g_Screen.GetDisplay()) > 0)
		{
			//Equivalent of WNDPROC
			XNextEvent(g_Screen.GetDisplay(), &event);
			switch(event.type)
			{
			case Expose:
				if(event.xexpose.count != 0)
				{
					break;
				}
				DrawGLScene();
				break;
			case ConfigureNotify:
				if((event.xconfigure.width != g_Screen.width) || (event.xconfigure.height != g_Screen.height))
				{
					g_Screen.width = event.xconfigure.width;
					g_Screen.height = event.xconfigure.height;
					printf("Resize event\n");
					ResizeGLScene(event.xconfigure.width, event.xconfigure.height);
				}
				break;
			case ButtonPress:
				keys[TranslateButton(event.xbutton.button)] = true;
				break;
			case ButtonRelease:
				keys[TranslateButton(event.xbutton.button)] = false;
				keys2[TranslateButton(event.xbutton.button)] = false;
				break;
			case KeyPress:
				keys[TranslateKey(XLookupKeysym(&event.xkey, 0))] = true;
				break;
			case KeyRelease:
				keys[TranslateKey(XLookupKeysym(&event.xkey, 0))] = false;
				keys2[TranslateKey(XLookupKeysym(&event.xkey, 0))] = false;
				break;
			case ClientMessage:
				if(*XGetAtomName(g_Screen.GetDisplay(), event.xclient.message_type) == *"WM_PROTOCOLS")
				{
					printf("Exiting sanely...\n");
					done = true;
				}
				break;
			default:
				break;
			}
			//End Equivalent of WNDPROC
			if(active)
			{
				if(keys[OpenArena::KEY_ESCAPE])
				{
					done = true;
				}
				else if(keys[OpenArena::KEY_F1])
				{
					g_Screen.Close();
					g_Screen.fullscreen = !g_Screen.fullscreen;
					g_Screen.Open();
				}
				else
				{
					level.defaultPlayer[0].camera.Update();

					if(!level.showConsole)
					{
						if(level.mlook)
						{
							level.defaultPlayer[0].camera.SetViewByMouse(g_Screen);
						}
						else
						{
#ifdef WIN32
							SetCursorPos(g_Screen.width/2, g_Screen.height/2);//Shit this may be windows specific
#endif
						}

						//Maybe some of these if not almost all should be moved into Level
						//////////
						//Move Backward
						if(!level.defaultPlayer->controls.backward.IsEmpty())
						{
							level.defaultPlayer->controls.backward.FirstPosition();
							if(keys[level.defaultPlayer->controls.backward.Retrieve()])
							{
								level.defaultPlayer->camera.MoveCamera(-level.moveSpeed);
							}
							else
							{
								while(level.defaultPlayer->controls.backward.NextPosition() && (keys[level.defaultPlayer->controls.backward.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.backward.Retrieve()])
									{
										level.defaultPlayer->camera.MoveCamera(-level.moveSpeed);
									}
								}
							}
						}

						//////////
						//Move forward
						if(!level.defaultPlayer->controls.forward.IsEmpty())
						{
							level.defaultPlayer->controls.forward.FirstPosition();
							if(keys[level.defaultPlayer->controls.forward.Retrieve()])
							{
								level.defaultPlayer->camera.MoveCamera(level.moveSpeed);
							}
							else
							{
								while(level.defaultPlayer->controls.forward.NextPosition() && (keys[level.defaultPlayer->controls.forward.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.forward.Retrieve()])
									{
										level.defaultPlayer->camera.MoveCamera(level.moveSpeed);
									}
								}
							}
						}

						//////////
						//Strafe Left
						if(!level.defaultPlayer->controls.moveLeft.IsEmpty())
						{
							level.defaultPlayer->controls.moveLeft.FirstPosition();
							if(keys[level.defaultPlayer->controls.moveLeft.Retrieve()])
							{
								level.defaultPlayer->camera.StrafeCamera(-level.moveSpeed);
							}
							else
							{
								while(level.defaultPlayer->controls.moveLeft.NextPosition() && (keys[level.defaultPlayer->controls.moveLeft.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.moveLeft.Retrieve()])
									{
										level.defaultPlayer->camera.StrafeCamera(-level.moveSpeed);
									}
								}
							}
						}

						//////////
						//Strafe Right
						if(!level.defaultPlayer->controls.moveRight.IsEmpty())
						{
							level.defaultPlayer->controls.moveRight.FirstPosition();
							if(keys[level.defaultPlayer->controls.moveRight.Retrieve()])
							{
								level.defaultPlayer[0].camera.StrafeCamera(level.moveSpeed);
							}
							else
							{
								while(level.defaultPlayer->controls.moveRight.NextPosition() && (keys[level.defaultPlayer->controls.moveRight.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.moveRight.Retrieve()])
									{
										level.defaultPlayer->camera.StrafeCamera(level.moveSpeed);
									}
								}
							}
						}

						//////////
						//Keyboard Look Left
						if(!level.defaultPlayer->controls.lookLeft.IsEmpty())
						{
							level.defaultPlayer->controls.lookLeft.FirstPosition();
							if(keys[level.defaultPlayer->controls.lookLeft.Retrieve()])
							{
								level.defaultPlayer[0].camera.RotateView(level.turnSpeed, 0, 1, 0);
							}
							else
							{
								while(level.defaultPlayer->controls.lookLeft.NextPosition() && (keys[level.defaultPlayer->controls.lookLeft.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.lookLeft.Retrieve()])
									{
										level.defaultPlayer[0].camera.RotateView(level.turnSpeed, 0, 1, 0);
									}
								}
							}
						}

						//////////
						//Keyboard Look Right
						if(!level.defaultPlayer->controls.lookRight.IsEmpty())
						{
							level.defaultPlayer->controls.lookRight.FirstPosition();
							if(keys[level.defaultPlayer->controls.lookRight.Retrieve()])
							{
								level.defaultPlayer->camera.RotateView(-level.turnSpeed, 0, 1, 0);
							}
							else
							{
								while(level.defaultPlayer->controls.lookRight.NextPosition() && (keys[level.defaultPlayer->controls.lookRight.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.lookRight.Retrieve()])
									{
										level.defaultPlayer->camera.RotateView(-level.turnSpeed, 0, 1, 0);
									}
								}
							}
						}

						//////////
						//Keyboard Look Up
						if(!level.defaultPlayer->controls.lookUp.IsEmpty())
						{
							level.defaultPlayer->controls.lookUp.FirstPosition();
							if(keys[level.defaultPlayer->controls.lookUp.Retrieve()])
							{
								level.defaultPlayer->camera.RotateView(level.turnSpeed, 1, 0, 0);
							}
							else
							{
								while(level.defaultPlayer->controls.lookUp.NextPosition() && (keys[level.defaultPlayer->controls.lookUp.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.lookUp.Retrieve()])
									{
										level.defaultPlayer->camera.RotateView(level.turnSpeed, 1, 0, 0);
									}
								}
							}
						}

						//////////
						//Keyboard Look Down
						if(!level.defaultPlayer->controls.lookDown.IsEmpty())
						{
							level.defaultPlayer->controls.lookDown.FirstPosition();
							if(keys[level.defaultPlayer->controls.lookDown.Retrieve()])
							{
								level.defaultPlayer->camera.RotateView(-level.turnSpeed, 1, 0, 0);
							}
							else
							{
								while(level.defaultPlayer->controls.lookDown.NextPosition() && (keys[level.defaultPlayer->controls.lookDown.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.lookDown.Retrieve()])
									{
										level.defaultPlayer->camera.RotateView(-level.turnSpeed, 1, 0, 0);
									}
								}
							}
						}

						//////////
						//Toggle Show FPS
						if(!level.defaultPlayer->controls.toggleFPS.IsEmpty())
						{
							level.defaultPlayer->controls.toggleFPS.FirstPosition();
							if(keys[level.defaultPlayer->controls.toggleFPS.Retrieve()])
							{
								if(!keys2[level.defaultPlayer->controls.toggleFPS.Retrieve()])
								{
									level.showFPS = !level.showFPS;
								}
							}
							else
							{
								while(level.defaultPlayer->controls.toggleFPS.NextPosition() && (keys[level.defaultPlayer->controls.toggleFPS.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.toggleFPS.Retrieve()])
									{
										if(!keys2[level.defaultPlayer->controls.toggleFPS.Retrieve()])
										{
											level.showFPS = !level.showFPS;
										}
									}
								}
							}
						}

						//////////
						//Toggle MouseLook
						if(!level.defaultPlayer->controls.toggleMouseLook.IsEmpty())
						{
							level.defaultPlayer->controls.toggleMouseLook.FirstPosition();
							if(keys[level.defaultPlayer->controls.toggleMouseLook.Retrieve()])
							{
								if(keys2[level.defaultPlayer->controls.toggleMouseLook.Retrieve()])
								{
									level.mlook = ! level.mlook;
								}
							}
							else
							{
								while(level.defaultPlayer->controls.toggleMouseLook.NextPosition() && (keys[level.defaultPlayer->controls.toggleMouseLook.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.toggleMouseLook.Retrieve()])
									{
										if(keys2[level.defaultPlayer->controls.toggleMouseLook.Retrieve()])
										{
											level.mlook = ! level.mlook;
										}
									}
								}
							}
						}

						//////////
						//Toggle Console
						if(!level.defaultPlayer[0].controls.toggleConsole.IsEmpty())
						{
							level.defaultPlayer[0].controls.toggleConsole.FirstPosition();
							if(keys[level.defaultPlayer[0].controls.toggleConsole.Retrieve()])
							{
								if(!keys2[level.defaultPlayer[0].controls.toggleConsole.Retrieve()])
								{
									level.showConsole = !level.showConsole;
									keys2[level.defaultPlayer[0].controls.toggleConsole.Retrieve()] = true;
								}
							}
							else
							{
								while(level.defaultPlayer[0].controls.toggleConsole.NextPosition() && (keys[level.defaultPlayer[0].controls.toggleConsole.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer[0].controls.toggleConsole.Retrieve()])
									{
										if(!keys2[level.defaultPlayer[0].controls.toggleConsole.Retrieve()])
										{
											level.showConsole = !level.showConsole;
											keys2[level.defaultPlayer[0].controls.toggleConsole.Retrieve()] = true;
										}
									}
								}
							}
						}

						//////////
						//Quick MouseLook
						if(!level.defaultPlayer->controls.quickMouseLook.IsEmpty())
						{
							level.defaultPlayer->controls.quickMouseLook.FirstPosition();
							if(keys[level.defaultPlayer->controls.quickMouseLook.Retrieve()])
							{
								if(keys2[level.defaultPlayer->controls.quickMouseLook.Retrieve()])
								{
									level.mlook = ! level.mlook;
								}
							}
							else
							{
								while(level.defaultPlayer->controls.quickMouseLook.NextPosition() && (keys[level.defaultPlayer->controls.quickMouseLook.Retrieve()] != true));
								{
									if(keys[level.defaultPlayer->controls.quickMouseLook.Retrieve()])
									{
										if(keys2[level.defaultPlayer->controls.quickMouseLook.Retrieve()])
										{
											level.mlook = ! level.mlook;
										}
									}
								}
							}
						}
					}
				}
			}

			DrawGLScene();

			if(keys[OpenArena::KEY_F1])
			{
				keys[OpenArena::KEY_F1] = false;
				g_Screen.Close();
				g_Screen.fullscreen = !g_Screen.fullscreen;
				if(!g_Screen.Open(OPENARENA_VERSION, level.screen.width, level.screen.height, level.screen.bpp, level.screen.fullscreen))
				{
					return 1;
				}
			}
		}
	}
	level.UnloadMap();
	g_Screen.Close();
	exit(0);
}

//This should probably be moved into oa_input
unsigned char TranslateKey(int keyCode)
{
	switch (keyCode)
	{
	case XK_BackSpace:
		return OpenArena::KEY_BACK;
	case XK_Tab:
		return OpenArena::KEY_TAB;
	case XK_Return:
		return OpenArena::KEY_RETURN;
	case XK_Escape:
		return OpenArena::KEY_ESCAPE;
	case XK_Left:
		return OpenArena::KEY_LEFT;
	case XK_Right:
		return OpenArena::KEY_RIGHT;
	case XK_Up:
		return OpenArena::KEY_UP;
	case XK_Down:
		return OpenArena::KEY_DOWN;
	case XK_Home:
		return OpenArena::KEY_HOME;
	case XK_End:
		return OpenArena::KEY_END;
	case XK_Prior:
		return OpenArena::KEY_PRIOR;
	case XK_Next:
		return OpenArena::KEY_NEXT;
	case XK_Num_Lock:
		return OpenArena::KEY_NUMLOCK;
	case XK_KP_Enter:
		return OpenArena::KEY_RETURN;
	case XK_KP_Home:
		return OpenArena::KEY_HOME;
	case XK_KP_End:
		return OpenArena::KEY_END;
	case XK_KP_Prior:
		return OpenArena::KEY_PRIOR;
	case XK_KP_Next:
		return OpenArena::KEY_NEXT;
	case XK_KP_0:
		return OpenArena::KEY_NUMPAD0;
	case XK_KP_1:
		return OpenArena::KEY_NUMPAD1;
	case XK_KP_2:
		return OpenArena::KEY_NUMPAD2;
	case XK_KP_3:
		return OpenArena::KEY_NUMPAD3;
	case XK_KP_4:
		return OpenArena::KEY_NUMPAD4;
	case XK_KP_5:
		return OpenArena::KEY_NUMPAD5;
	case XK_KP_6:
		return OpenArena::KEY_NUMPAD6;
	case XK_KP_7:
		return OpenArena::KEY_NUMPAD7;
	case XK_KP_8:
		return OpenArena::KEY_NUMPAD8;
	case XK_KP_9:
		return OpenArena::KEY_NUMPAD9;
	case XK_KP_Multiply:
		return OpenArena::KEY_MULTIPLY;
	case XK_KP_Add:
		return OpenArena::KEY_ADD;
	case XK_KP_Subtract:
		return OpenArena::KEY_SUBTRACT;
	case XK_KP_Divide:
		return OpenArena::KEY_DIVIDE;
	case XK_F1:
		return OpenArena::KEY_F1;
	case XK_F2:
		return OpenArena::KEY_F2;
	case XK_F3:
		return OpenArena::KEY_F3;
	case XK_F4:
		return OpenArena::KEY_F4;
	case XK_F5:
		return OpenArena::KEY_F5;
	case XK_F6:
		return OpenArena::KEY_F6;
	case XK_F7:
		return OpenArena::KEY_F7;
	case XK_F8:
		return OpenArena::KEY_F8;
	case XK_F9:
		return OpenArena::KEY_F9;
	case XK_F10:
		return OpenArena::KEY_F10;
	case XK_F11:
		return OpenArena::KEY_F11;
	case XK_F12:
		return OpenArena::KEY_F12;
	case XK_Shift_L:
		return OpenArena::KEY_SHIFT;
	case XK_Shift_R:
		return OpenArena::KEY_SHIFT;
	case XK_Control_L:
		return OpenArena::KEY_CONTROL;
	case XK_Control_R:
		return OpenArena::KEY_CONTROL;
	case XK_Caps_Lock:
		return OpenArena::KEY_CAPITAL;
	case XK_Pause:
		return OpenArena::KEY_PAUSE;
	case XK_KP_Space:
		return OpenArena::KEY_SPACE;
	case XK_Insert:
		return OpenArena::KEY_INSERT;
	case XK_Delete:
		return OpenArena::KEY_DELETE;
	case XK_KP_Separator:
		return OpenArena::KEY_SEPARATOR;
	case XK_Scroll_Lock:
		return OpenArena::KEY_SCROLL;
	case XK_period:
		return OpenArena::KEY_OEM_PERIOD;
	case XK_plus:
		return OpenArena::KEY_OEM_PLUS;
	case XK_minus:
		return OpenArena::KEY_OEM_MINUS;
	case XK_comma:
		return OpenArena::KEY_OEM_COMMA;
	case XK_0:
		return OpenArena::KEY_0;
	case XK_1:
		return OpenArena::KEY_1;
	case XK_2:
		return OpenArena::KEY_2;
	case XK_3:
		return OpenArena::KEY_3;
	case XK_4:
		return OpenArena::KEY_4;
	case XK_5:
		return OpenArena::KEY_5;
	case XK_6:
		return OpenArena::KEY_6;
	case XK_7:
		return OpenArena::KEY_7;
	case XK_8:
		return OpenArena::KEY_8;
	case XK_9:
		return OpenArena::KEY_9;
	case XK_A:
		return OpenArena::KEY_A;
	case XK_B:
		return OpenArena::KEY_B;
	case XK_C:
		return OpenArena::KEY_C;
	case XK_D:
		return OpenArena::KEY_D;
	case XK_E:
		return OpenArena::KEY_E;
	case XK_F:
		return OpenArena::KEY_F;
	case XK_G:
		return OpenArena::KEY_G;
	case XK_H:
		return OpenArena::KEY_H;
	case XK_I:
		return OpenArena::KEY_I;
	case XK_J:
		return OpenArena::KEY_J;
	case XK_K:
		return OpenArena::KEY_K;
	case XK_L:
		return OpenArena::KEY_L;
	case XK_M:
		return OpenArena::KEY_M;
	case XK_N:
		return OpenArena::KEY_N;
	case XK_O:
		return OpenArena::KEY_O;
	case XK_P:
		return OpenArena::KEY_P;
	case XK_Q:
		return OpenArena::KEY_Q;
	case XK_R:
		return OpenArena::KEY_R;
	case XK_S:
		return OpenArena::KEY_S;
	case XK_T:
		return OpenArena::KEY_T;
	case XK_U:
		return OpenArena::KEY_U;
	case XK_V:
		return OpenArena::KEY_V;
	case XK_W:
		return OpenArena::KEY_W;
	case XK_X:
		return OpenArena::KEY_X;
	case XK_Y:
		return OpenArena::KEY_Y;
	case XK_Z:
		return OpenArena::KEY_Z;

/*These keys definately still need to be accounted for
#define KEY_LBUTTON		1
#define KEY_RBUTTON		2
#define KEY_MBUTTON 	3
#define KEY_LWIN		21
#define KEY_RWIN		22
#define KEY_APPS		23
#define KEY_OEM_1		53
#define KEY_OEM_2		54
#define KEY_OEM_3		55
#define KEY_OEM_4		56
#define KEY_OEM_5		57
#define KEY_OEM_6		58
#define KEY_OEM_7		59
*/
	default:
		return OpenArena::KEY_UNKNOWN;
	}
}

unsigned char TranslateButton(int keyCode)
{
	switch(keyCode)
	{
		case Button1:
			return OpenArena::KEY_BUTTON0;
		case Button2:
			return OpenArena::KEY_BUTTON1;
		case Button3:
			return OpenArena::KEY_BUTTON2;
		case Button4:
			return OpenArena::KEY_BUTTON3;
		case Button5:
			return OpenArena::KEY_BUTTON4;
	}
}
#endif
