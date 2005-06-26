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
int InitGL();
void KillGLWindow();

static int attrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};
static int attrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};

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

//
//void KillGLWindow()
//	Purpose:
//		To do all required setup before creating an OpenGL window
void KillGLWindow()
{
	if(g_Screen.hRC)
	{
		if(!glXMakeCurrent(g_Screen.display, None, NULL))
		{
			printf("Could not release drawing context.\n");
		}
		glXDestroyContext(g_Screen.display, g_Screen.hRC);
		g_Screen.hRC = NULL;
	}

	if(g_Screen.fullscreen)
	{
		XF86VidModeSwitchToMode(g_Screen.display, g_Screen.screen, &g_Screen.vidMode);
		XF86VidModeSetViewPort(g_Screen.display, g_Screen.screen, 0, 0);
	}
	XCloseDisplay(g_Screen.display);
}

//
//bool CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag)
//	Purpose:
//		
bool CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag)
{
	XVisualInfo* vi;
	Colormap cmap;
	int bestMode = 0;
	int vidModeMajorVersion;
	int vidModeMinorVersion;
	int glxMajorVersion;
	int glxMinorVersion;
	int modeNum;
	XF86VidModeModeInfo** modes;
	Atom  wmDelete;
	Window winDummy;
	unsigned int borderDummy;

	g_Screen.name = title;
	g_Screen.width = width;
	g_Screen.height = height;
	g_Screen.bpp = bits;
	g_Screen.fullscreen = fullscreenflag;

	g_Screen.display = XOpenDisplay(0);
	g_Screen.screen = DefaultScreen(g_Screen.display);
	XF86VidModeQueryVersion(g_Screen.display, &vidModeMajorVersion, &vidModeMinorVersion);
	printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion, vidModeMinorVersion);

	XF86VidModeGetAllModeLines(g_Screen.display, g_Screen.screen, &modeNum, &modes);
	g_Screen.vidMode = *modes[0];

	int i;
	for(i=0; i<modeNum; i++)
	{
		//Add a check for colordepth here
		if((modes[i]->hdisplay == width) && (modes[i]->vdisplay == height))
		{
			bestMode = i;
		}
	}

	vi = glXChooseVisual(g_Screen.display, g_Screen.screen, attrListDbl);
	if(vi == NULL)
	{
		vi = glXChooseVisual(g_Screen.display, g_Screen.screen, attrListSgl);
		g_Screen.doubleBuffered = false;
		printf("Only Singlebuffered Visual!\n");
	}
	else
	{
		g_Screen.doubleBuffered = true;
		printf("Got Doublebuffered Visual!\n");
	}

	glXQueryVersion(g_Screen.display, &glxMajorVersion, & glxMinorVersion);
	printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);

	g_Screen.hRC = glXCreateContext(g_Screen.display, vi, 0, GL_TRUE);
	cmap = XCreateColormap(g_Screen.display, RootWindow(g_Screen.display, vi->screen), vi->visual, AllocNone);
	g_Screen.attributes.colormap = cmap;
	g_Screen.attributes.border_pixel = 0;

	if(g_Screen.fullscreen)
	{
		XF86VidModeSwitchToMode(g_Screen.display, g_Screen.screen, modes[bestMode]);
		XF86VidModeSetViewPort(g_Screen.display, g_Screen.screen, 0, 0);
		XFree(modes);

		g_Screen.attributes.override_redirect = true;
		g_Screen.attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
		g_Screen.window = XCreateWindow(g_Screen.display, RootWindow(g_Screen.display, vi->screen), 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &g_Screen.attributes);
		XWarpPointer(g_Screen.display, None, g_Screen.window, 0, 0, 0, 0, 0, 0);
		XMapRaised(g_Screen.display, g_Screen.window);
		XGrabKeyboard(g_Screen.display, g_Screen.window, true, GrabModeAsync, GrabModeAsync, CurrentTime);
		XGrabPointer(g_Screen.display, g_Screen.window, true, ButtonPressMask, GrabModeAsync, GrabModeAsync, g_Screen.window, None, CurrentTime);
	}
	else
	{
		g_Screen.attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
		g_Screen.window = XCreateWindow(g_Screen.display, RootWindow(g_Screen.display, vi->screen), 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &g_Screen.attributes);
		wmDelete = XInternAtom(g_Screen.display, "WM_DELETE_WINDOW", true);
		XSetWMProtocols(g_Screen.display, g_Screen.window, &wmDelete, 1);
		XSetStandardProperties(g_Screen.display, g_Screen.window, title.c_str(), title.c_str(), None, NULL, 0, NULL);
		XMapRaised(g_Screen.display, g_Screen.window);
	}

	glXMakeCurrent(g_Screen.display, g_Screen.window, g_Screen.hRC);
	unsigned int twidth, theight, depth;
	XGetGeometry(g_Screen.display, g_Screen.window, &winDummy, &g_Screen.x, &g_Screen.y, &twidth, &theight, &borderDummy, &depth);
	g_Screen.bpp = (char)depth;
	g_Screen.height = (short)twidth;
	g_Screen.width = (short)theight;
	printf("Depth %d\n", g_Screen.bpp);
	if(glXIsDirect(g_Screen.display, g_Screen.hRC))
	{
		printf("Congrats, you have Direct Rendering!\n");
	}
	else
	{
		printf("Sorry, no Direct Rendering possible!\n");
	}
	InitGL();
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

	if(!CreateGLWindow(OPENARENA_VERSION, level.screen.width, level.screen.height, level.screen.bpp, level.screen.fullscreen))
	{
		return 1;
	}

	while(!done)
	{
		while(XPending(g_Screen.display) > 0)
		{
			//Equivalent of WNDPROC
			XNextEvent(g_Screen.display, &event);
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
				done = true;
				break;
			case KeyPress:
				keys[TraslateKey(XLookupKeysym(&event.xkey, 0))] = true;
				//Remove this later it shouldn't be needed
				if(XLookupKeysym(&event.xkey, 0) == XK_Escape)
				{
				done = true;
				}
				if(XLookupKeysym(&event.xkey, 0) == XK_F1)
				{
					KillGLWindow();
					g_Screen.fullscreen = !g_Screen.fullscreen;
					CreateGLWindow("Blah Blah Blah", 640, 480, 24, g_Screen.fullscreen);
				}
				break;
			case ClientMessage:
				if(*XGetAtomName(g_Screen.display, event.xclient.message_type) == *"WM_PROTOCOLS")
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
				if(keys[KEY_ESCAPE])
				{
					done = true;
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

			if(keys[KEY_F1])
			{
				keys[KEY_F1] = false;
				KillGLWindow();
				g_Screen.fullscreen = !g_Screen.fullscreen;
				if(!CreateGLWindow(OPENARENA_VERSION, level.screen.width, level.screen.height, level.screen.bpp, level.screen.fullscreen))
				{
					return 1;
				}
			}
		}
	}
	level.UnloadMap();
	KillGLWindow();
	exit(0);
}

//This should probably be moved into oa_input
usigned char TranslateKey(int keyCode)
{
	switch (keyCode)
	{
	case XK_BackSpace:
		return KEY_BACK;
	case XK_Tab:
		return KEY_TAB;
	case XK_Return:
		return KEY_RETURN;
	case XK_Escape:
		return KEY_ESCAPE;
	case XK_Left:
		return KEY_LEFT;
	case XK_Right:
		return KEY_RIGHT;
	case XK_Up:
		return KEY_UP;
	case XK_Down:
		return KEY_DOWN;
	case XK_Home:
		return KEY_HOME;
	case XK_End:
		return KEY_END;
	case XK_Prior:
		return KEY_PRIOR;
	case XK_Next:
		return KEY_NEXT;
	case XK_Num_Lock:
		return KEY_NUMLOCK;
	case XK_KP_Enter:
		return KEY_RETURN;
	case XK_KP_Home:
		return KEY_HOME;
	case XK_KP_End:
		return KEY_END;
	case XK_KP_Prior:
		return KEY_PRIOR;
	case XK_KP_Next:
		return KEY_NEXT;
	case XK_KP_0:
		return KEY_NUMPAD0;
	case XK_KP_1:
		return KEY_NUMPAD1;
	case XK_KP_2:
		return KEY_NUMPAD2;
	case XK_KP_3;
		return KEY_NUMPAD3;
	case XK_KP_4:
		return KEY_NUMPAD4;
	case XK_KP_5:
		return KEY_NUMPAD5;
	case XK_KP_6:
		return KEY_NUMPAD6;
	case XK_KP_7:
		return KEY_NUMPAD7;
	case XK_KP_8:
		return KEY_NUMPAD8;
	case XK_KP_9:
		return KEY_NUMPAD9;
	case XK_KP_Multiply:
		return KEY_MULTIPLY;
	case XK_KP_Add:
		return KEY_ADD;
	case XK_KP_Subtract:
		return KEY_SUBTRACT;
	case XK_KP_Divide:
		return KEY_DIVIDE;
	case XK_F1:
		return KEY_F1:
	case XK_F2:
		return KEY_F2:
	case XK_F3;
		return KEY_F3:
	case XK_F4:
		return KEY_F4:
	case XK_F5:
		return KEY_F5:
	case XK_F6:
		return KEY_F6:
	case XK_F7:
		return KEY_F7:
	case XK_F8:
		return KEY_F8:
	case XK_F9:
		return KEY_F9:
	case XK_F10:
		return KEY_F10:
	case XK_F11:
		return KEY_F11:
	case XK_F12:
		return KEY_F12:
	case XK_Shift_L:
		return KEY_SHIFT;
	case XK_Shift_R:
		return KEY_SHIFT;
	case XK_Control_L:
		return KEY_CONTROL;
	case XK_Control_R:
		return KEY_CONTROL;
	case XK_Caps_Lock:
		return KEY_CAPITAL;
	case XK_Pause:
		return KEY_PAUSE;
	case XK_KP_Space:
		return KEY_SPACE;
	case XK_Insert:
		return KEY_INSERT;
	case XK_Delete:
		return KEY_DELETE;
	case XK_KP_Separator:
		return KEY_SEPARATOR;
	case XK_Scroll_Lock:
		return KEY_SCROLL;
	case XK_period:
		return KEY_OEM_PERIOD;
	case XK_plus:
		return KEY_OEM_PLUS;
	case XK_minus:
		return KEY_OEM_MINUS;
	case XK_comma:
		return KEY_OEM_COMMA;
	case XK_0:
		return KEY_0;
	case XK_1:
		return KEY_1;
	case XK_2:
		return KEY_2;
	case XK_3:
		return KEY_3;
	case XK_4:
		return KEY_4;
	case XK_5:
		return KEY_5;
	case XK_6:
		return KEY_6;
	case XK_7:
		return KEY_7;
	case XK_8:
		return KEY_8;
	case XK_9:
		return KEY_9;
	case XK_A:
		return KEY_A;
	case XK_B:
		return KEY_B;
	case XK_C:
		return KEY_C;
	case XK_D:
		return KEY_D;
	case XK_E:
		return KEY_E;
	case XK_F:
		return KEY_F;
	case XK_G:
		return KEY_G;
	case XK_H:
		return KEY_H;
	case XK_I:
		return KEY_I;
	case XK_J:
		return KEY_J;
	case XK_K:
		return KEY_K;
	case XK_L:
		return KEY_L;
	case XK_M:
		return KEY_M;
	case XK_N:
		return KEY_N;
	case XK_O:
		return KEY_O;
	case XK_P:
		return KEY_P;
	case XK_Q:
		return KEY_Q;
	case XK_R:
		return KEY_R;
	case XK_S:
		return KEY_S;
	case XK_T:
		return KEY_T;
	case XK_U:
		return KEY_U;
	case XK_V:
		return KEY_V;
	case XK_W:
		return KEY_W;
	case XK_X:
		return KEY_X;
	case XK_Y:
		return KEY_Y;
	case XK_Z:
		return KEY_Z;

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
		return KEY_UNKNOWN;
	}
}

#endif
