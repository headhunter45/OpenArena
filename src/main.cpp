////////////////////////////////////////////////////////////////////////////////
//
//	Module:		main.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	10-20-2003
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

//include necessary header files
#include "../include/main.h"

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
bool CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag);
void KillGLWindow();
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

void KillGLWindow()
{
	if (g_Screen.fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true/*false*/);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		if (!wglDeleteContext(hRC))
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		hRC=NULL;
	}

	if (hDC && !ReleaseDC(g_hWnd, hDC))
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;
	}

	if (g_hWnd && !DestroyWindow(g_hWnd))
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		g_hWnd=NULL;
	}

	if (!UnregisterClass("OpenArena v0.1.0", hInstance))
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;
	}
}

bool CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag)
{
	unsigned int PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;

	g_Screen.fullscreen = fullscreenflag;
	g_Screen.width = width;
	g_Screen.height = height;
	g_Screen.bpp = bits;
	g_Screen.name = title;

	hInstance	= GetModuleHandle(NULL);
	wc.style	= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenArena v0.1.0";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (g_Screen.fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;


		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","OpenArena",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
				g_Screen.fullscreen = false;
			else
			{

				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return false;
			}
		}
	}

	if (g_Screen.fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(/*true*/false);
	}
	else
	{
		ShowCursor(false);
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

	if (!(g_hWnd = CreateWindowEx(dwExStyle, "OpenArena v0.1.0", title.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, NULL, NULL, hInstance, NULL)))
	{
		KillGLWindow();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	static	PIXELFORMATDESCRIPTOR pfd={sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, bits, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

	if (!(hDC=GetDC(g_hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!wglMakeCurrent(hDC,hRC))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(g_hWnd,SW_SHOW);
	SetForegroundWindow(g_hWnd);
	SetFocus(g_hWnd);
	ReSizeGLScene(width, height);

	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	return true;
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
				level.defaultPlayer[0].controls.toggleConsole.FirstPosition();
				if(wParam == level.defaultPlayer[0].controls.toggleConsole.Retrieve())
				{
					level.showConsole = false;
				}
				else
				{
					while(level.defaultPlayer[0].controls.toggleConsole.NextPosition() && level.showConsole)
					{
						if(level.defaultPlayer[0].controls.toggleConsole.Retrieve() == wParam)
						{
							level.showConsole = false;
						}
					}
				}

				if(wParam == VK_RETURN)
				{
					level.UpdateConsole('\n');
				}
				else if(wParam == VK_SPACE)
				{
					level.UpdateConsole(' ');
				}
				else if(wParam == VK_BACK)
				{
					level.UpdateConsole(VK_BACK);
				}
				else if(isalpha(uint8(wParam)))
				{
					level.UpdateConsole(wParam);
				}
			}
			else
			{
				keys[wParam] = true;
				return 0;
			}
		}
	case WM_KEYUP:
		{
			keys[wParam] = false;
			keys2[wParam] = false;
			return 0;
		}
	case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			keys[VK_LBUTTON] = true;
			return 0;
		}
	case WM_LBUTTONUP:
		{
			keys[VK_LBUTTON] = false;
			keys[VK_LBUTTON] = false;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			keys[VK_RBUTTON] = true;
			return 0;
		}
	case WM_RBUTTONUP:
		{
			keys[VK_RBUTTON] = false;
			keys[VK_RBUTTON] = false;
			return 0;
		}
	case WM_MBUTTONDOWN:
		{
			keys[VK_MBUTTON] = true;
			return 0;
		}
	case WM_MBUTTONUP:
		{
			keys[VK_MBUTTON] = false;
			keys[VK_MBUTTON] = false;
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

	g_Screen.name = "OpenArena v0.1.0";
	g_Screen.width = level.screen.width;
	g_Screen.height = level.screen.height;
	g_Screen.bpp = level.screen.bpp;
	g_Screen.fullscreen = level.screen.fullscreen;

	level.glFont.SetScreenDimensions(g_Screen.width*2, g_Screen.height*2);
	//level.glFont.BuildFont("oa\\textures\\menu\\font.bmp");//(level.gamedir + "\\textures\\menu\\font.bmp").c_str());
	if (level.nextLevel != "")
		level.LoadMap();
	else
		level.LoadMap("intro.map");

	if (!CreateGLWindow(g_Screen.name, g_Screen.width, g_Screen.height, g_Screen.bpp, g_Screen.fullscreen))
	{
		return 0;
	}



	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
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
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done=true;
				}
				else	
				{
					level.defaultPlayer[0].camera.Update();

					if(level.showConsole)
					{
						if(keys['I'] && !keys2['I'])
							level.showConsole = false;
						//level.UpdateConsole('\n');
					}
					else
					{
						if (level.mlook)
						{
							level.defaultPlayer[0].camera.SetViewByMouse(g_Screen);
						}
						else
						{
							SetCursorPos(g_Screen.width/2, g_Screen.height/2);
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

			SwapBuffers(hDC);

			if (keys[VK_F1])
			{
				keys[VK_F1]=false;
				KillGLWindow();
				g_Screen.fullscreen=!g_Screen.fullscreen;
				if (!CreateGLWindow("OpenArena",g_Screen.width,g_Screen.height,g_Screen.bpp,g_Screen.fullscreen))
				{
					return 0;
				}
			}
		}
	}

	level.UnloadMap();
	KillGLWindow();
	return (msg.wParam);
}
