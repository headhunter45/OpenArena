////////////////////////////////////////////////////////////////////////////////
//
//	Module:		windows.cpp
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
#ifdef WIN32
//include necessary header files
#include "../include/main.h"
#include "../include/version.h"

//link necessary libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "winmm.lib")

//Ensure CDS_FULLSCREEN is defined
#ifndef CDS_FULLSCREEN
#define CDS_FULLSCREEN 4
#endif

using namespace std;

void InitControls();
int InitGL(GLvoid);
void ReSizeGLScene(GLsizei width, GLsizei height);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
OpenArena::Keys TranslateKey(int keyCode);
void HandleConsoleKeyPress(OpenArena::Keys key);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions

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
//	int InitGL(GLvoid)
//	Purpose:
//		To do all required setup before creating an OpenGL window
//	Pre:
//
//	Post:
//

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

//
//	GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
//	Purpose:
//		To resize the OpenGL window also called on creation
//	Pre:
//
//	Post:
//

void ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height==0)
		height=1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

LRESULT CALLBACK WndProc(HWND	hWnd,
						 UINT	uMsg,
						 WPARAM	wParam,
						 LPARAM	lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		{
			if (!HIWORD(wParam))
			{
				active=true;
			}
			else
			{
				active=false;
			}

			return 0;
		}
	case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			break;
		}
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN:
		{
			if(level.showConsole)
			{
				HandleConsoleKeyPress((OpenArena::Keys)TranslateKey(wParam));
			}
			else
			{
				keys[TranslateKey(wParam)] = true;
			}
 			return 0;
		}
	case WM_KEYUP:
		{
			keys[TranslateKey(wParam)] = false;
			keys2[TranslateKey(wParam)] = false;
			return 0;
		}
	case WM_SYSKEYDOWN:
		break;
	case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			keys[OpenArena::KEY_LBUTTON] = true;
			return 0;
		}
	case WM_LBUTTONUP:
		{
			keys[OpenArena::KEY_LBUTTON] = false;
			keys[OpenArena::KEY_LBUTTON] = false;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			keys[OpenArena::KEY_RBUTTON] = true;
			return 0;
		}
	case WM_RBUTTONUP:
		{
			keys[OpenArena::KEY_RBUTTON] = false;
			keys[OpenArena::KEY_RBUTTON] = false;
			return 0;
		}
	case WM_MBUTTONDOWN:
		{
			keys[OpenArena::KEY_MBUTTON] = true;
			return 0;
		}
	case WM_MBUTTONUP:
		{
			keys[OpenArena::KEY_MBUTTON] = false;
			keys[OpenArena::KEY_MBUTTON] = false;
			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,
				   HINSTANCE	hPrevInstance,
				   LPSTR		lpCmdLine,
				   int		nCmdShow)
{
	MSG	msg;
	bool done=false;


	if (strlen(lpCmdLine))
		level.ParseCmds(lpCmdLine);

	InitControls();

	level.glFont.SetScreenDimensions(level.screen.GetWidth()*2, level.screen.GetHeight()*2);
	//level.glFont.BuildFont("oa\\textures\\menu\\font.bmp");//(level.gamedir + "\\textures\\menu\\font.bmp").c_str());
	if (level.nextLevel == "")
	{
		level.LoadMap("intro.map");
	}
	else
	{
		level.LoadMap();
	}

	g_Screen.SetOnInit(InitGL);
	g_Screen.SetOnResize(ReSizeGLScene);
	if (!g_Screen.Open(string(OPENARENA_VERSION), level.screen.GetWidth(), level.screen.GetHeight(), level.screen.GetColorDepth(), level.screen.GetFullscreen()))
	{
		return 0;
	}

	while(!done)
	{
		while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	
		if (active)
		{
			if (keys[OpenArena::KEY_ESCAPE])
			{
				done=true;
			}
			else	
			{
				level.defaultPlayer[0].camera.Update();

				if(!level.showConsole)
				{
					if (level.mlook)
					{
						level.defaultPlayer[0].camera.SetViewByMouse(g_Screen);
					}
					else
					{
						SetCursorPos(g_Screen.GetWidth()/2, g_Screen.GetHeight()/2);
					}

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
					//level.Render();
				}
				level.Render();
				//
			}
		}

		g_Screen.SwapBuffers();

		if (keys[OpenArena::KEY_F1])
		{
			keys[OpenArena::KEY_F1]=false;
			g_Screen.Close();
			g_Screen.ToggleFullscreen();
			if (!g_Screen.Open("OpenArena",g_Screen.GetWidth(),g_Screen.GetHeight(),g_Screen.GetColorDepth(),g_Screen.GetFullscreen()))
			{
				return 0;
			}
		}
	}

	level.UnloadMap();
	g_Screen.Close();
	return (msg.wParam);
}

OpenArena::Keys TranslateKey(int keyCode)
{
	switch (keyCode)
	{
	case VK_LEFT:
		return OpenArena::KEY_LEFT;
	case VK_RIGHT:
		return OpenArena::KEY_RIGHT;
	case VK_UP:
		return OpenArena::KEY_UP;
	case VK_DOWN:
		return OpenArena::KEY_DOWN;
	case VK_SPACE:
		return OpenArena::KEY_SPACE;
	case VK_RETURN:
		return OpenArena::KEY_RETURN;
	case VK_SHIFT:
		return OpenArena::KEY_SHIFT;
	case VK_PAUSE:
		return OpenArena::KEY_PAUSE;
	case VK_CONTROL:
		return OpenArena::KEY_CONTROL;
	case VK_CAPITAL:
		return OpenArena::KEY_CAPITAL;
	case VK_ESCAPE:
		return OpenArena::KEY_ESCAPE;
	case VK_PRIOR:
		return OpenArena::KEY_PRIOR;
	case VK_NEXT:
		return OpenArena::KEY_NEXT;
	case VK_END:
		return OpenArena::KEY_END;
	case VK_HOME:
		return OpenArena::KEY_HOME;
	case VK_INSERT:
		return OpenArena::KEY_INSERT;
	case VK_DELETE:
		return OpenArena::KEY_DELETE;
	case VK_LWIN:
		return OpenArena::KEY_LWIN;
	case VK_RWIN:
		return OpenArena::KEY_RWIN;
	case VK_APPS:
		return OpenArena::KEY_APPS;
	case VK_NUMPAD0:
		return OpenArena::KEY_NUMPAD0;
	case VK_NUMPAD1:
		return OpenArena::KEY_NUMPAD1;
	case VK_NUMPAD2:
		return OpenArena::KEY_NUMPAD2;
	case VK_NUMPAD3:
		return OpenArena::KEY_NUMPAD3;
	case VK_NUMPAD4:
		return OpenArena::KEY_NUMPAD4;
	case VK_NUMPAD5:
		return OpenArena::KEY_NUMPAD5;
	case VK_NUMPAD6:
		return OpenArena::KEY_NUMPAD6;
	case VK_NUMPAD7:
		return OpenArena::KEY_NUMPAD7;
	case VK_NUMPAD8:
		return OpenArena::KEY_NUMPAD8;
	case VK_NUMPAD9:
		return OpenArena::KEY_NUMPAD9;
	case VK_MULTIPLY:
		return OpenArena::KEY_MULTIPLY;
	case VK_ADD:
		return OpenArena::KEY_ADD;
	case VK_SUBTRACT:
		return OpenArena::KEY_SUBTRACT;
	case VK_DIVIDE:
		return OpenArena::KEY_DIVIDE;
	case VK_F1:
		return OpenArena::KEY_F1;
	case VK_F2:
		return OpenArena::KEY_F2;
	case VK_F3:
		return OpenArena::KEY_F3;
	case VK_F4:
		return OpenArena::KEY_F4;
	case VK_F5:
		return OpenArena::KEY_F5;
	case VK_F6:
		return OpenArena::KEY_F6;
	case VK_F7:
		return OpenArena::KEY_F7;
	case VK_F8:
		return OpenArena::KEY_F8;
	case VK_F9:
		return OpenArena::KEY_F9;
	case VK_F10:
		return OpenArena::KEY_F10;
	case VK_F11:
		return OpenArena::KEY_F11;
	case VK_F12:
		return OpenArena::KEY_F12;
	case VK_NUMLOCK:
		return OpenArena::KEY_NUMLOCK;
	case VK_SCROLL:
		return OpenArena::KEY_SCROLL;
	case VK_SEPARATOR:
		return OpenArena::KEY_SEPARATOR;
	case VK_OEM_1:
		return OpenArena::KEY_OEM_1;
	case VK_OEM_2:
		return OpenArena::KEY_OEM_2;
	case VK_OEM_3:
		return OpenArena::KEY_OEM_3;
	case VK_OEM_4:
		return OpenArena::KEY_OEM_4;
	case VK_OEM_5:
		return OpenArena::KEY_OEM_5;
	case VK_OEM_6:
		return OpenArena::KEY_OEM_6;
	case VK_OEM_7:
		return OpenArena::KEY_OEM_7;
	case VK_OEM_PERIOD:
		return OpenArena::KEY_OEM_PERIOD;
	case VK_OEM_PLUS:
		return OpenArena::KEY_OEM_PLUS;
	case VK_OEM_MINUS:
		return OpenArena::KEY_OEM_MINUS;
	case VK_OEM_COMMA:
		return OpenArena::KEY_OEM_COMMA;
	case VK_BACK:
		return OpenArena::KEY_BACK;
	case VK_TAB:
		return OpenArena::KEY_TAB;
	case '0':
		return OpenArena::KEY_0;
	case '1':
		return OpenArena::KEY_1;
	case '2':
		return OpenArena::KEY_2;
	case '3':
		return OpenArena::KEY_3;
	case '4':
		return OpenArena::KEY_4;
	case '5':
		return OpenArena::KEY_5;
	case '6':
		return OpenArena::KEY_6;
	case '7':
		return OpenArena::KEY_7;
	case '8':
		return OpenArena::KEY_8;
	case '9':
		return OpenArena::KEY_9;
	case 'A':
		return OpenArena::KEY_A;
	case 'B':
		return OpenArena::KEY_B;
	case 'C':
		return OpenArena::KEY_C;
	case 'D':
		return OpenArena::KEY_D;
	case 'E':
		return OpenArena::KEY_E;
	case 'F':
		return OpenArena::KEY_F;
	case 'G':
		return OpenArena::KEY_G;
	case 'H':
		return OpenArena::KEY_H;
	case 'I':
		return OpenArena::KEY_I;
	case 'J':
		return OpenArena::KEY_J;
	case 'K':
		return OpenArena::KEY_K;
	case 'L':
		return OpenArena::KEY_L;
	case 'M':
		return OpenArena::KEY_M;
	case 'N':
		return OpenArena::KEY_N;
	case 'O':
		return OpenArena::KEY_O;
	case 'P':
		return OpenArena::KEY_P;
	case 'Q':
		return OpenArena::KEY_Q;
	case 'R':
		return OpenArena::KEY_R;
	case 'S':
		return OpenArena::KEY_S;
	case 'T':
		return OpenArena::KEY_T;
	case 'U':
		return OpenArena::KEY_U;
	case 'V':
		return OpenArena::KEY_V;
	case 'W':
		return OpenArena::KEY_W;
	case 'X':
		return OpenArena::KEY_X;
	case 'Y':
		return OpenArena::KEY_Y;
	case 'Z':
		return OpenArena::KEY_Z;
	case VK_LBUTTON:
		return OpenArena::KEY_LBUTTON;
	case VK_RBUTTON:
		return OpenArena::KEY_RBUTTON;
	case VK_MBUTTON:
		return OpenArena::KEY_MBUTTON;
	default:
		return OpenArena::KEY_UNKNOWN;
	}
}

void HandleConsoleKeyPress(OpenArena::Keys key)
{
	//See if we need to hide the console
	level.defaultPlayer[0].controls.toggleConsole.FirstPosition();
	if(key == level.defaultPlayer[0].controls.toggleConsole.Retrieve())
	{
		level.showConsole = false;
	}
	else
	{
		while(level.defaultPlayer[0].controls.toggleConsole.NextPosition() && level.showConsole)
		{
			if(level.defaultPlayer[0].controls.toggleConsole.Retrieve() == key)
			{
				level.showConsole = false;
			}
		}
	}
	switch (key)
	{
	case OpenArena::KEY_SHIFT:
		keys[OpenArena::KEY_SHIFT] = true;
		break;
	case OpenArena::KEY_RETURN:
		level.UpdateConsole('\n');
		break;
	case OpenArena::KEY_SPACE:
		printf("hello");
		level.UpdateConsole(' ');
		break;
	case OpenArena::KEY_BACK:
		level.UpdateConsole(OpenArena::KEY_BACK);
		break;
	default:
		char ascii = OpenArena::KeyToASCII(key, keys[OpenArena::KEY_SHIFT]);
		if(ascii != '\0')
		{
			level.UpdateConsole(ascii);
		}
	}
}


#endif