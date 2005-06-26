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
				//See if we need to hide the console
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
				else if(wParam == VK_SHIFT)
				{
					keys[VK_SHIFT] = true;
				}
				else if(wParam == VK_SPACE)
				{
					level.UpdateConsole(' ');
				}
				else if(wParam == VK_BACK)
				{
					level.UpdateConsole(VK_BACK);
				}
				else if(wParam == VK_OEM_1)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole(':');
					}
					else
					{
						level.UpdateConsole(';');
					}
				}
				else if(wParam == VK_OEM_2)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('?');
					}
					else
					{
						level.UpdateConsole('/');
					}
				}
				else if(wParam == VK_OEM_3)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('~');
					}
					else
					{
						level.UpdateConsole('`');
					}
				}
				else if(wParam == VK_OEM_4)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('{');
					}
					else
					{
						level.UpdateConsole('[');
					}
				}
				else if(wParam == VK_OEM_5)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('|');
					}
					else
					{
						level.UpdateConsole('\\');
					}
				}
				else if(wParam == VK_OEM_6)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('}');
					}
					else
					{
						level.UpdateConsole(']');
					}
				}
				else if(wParam == VK_OEM_7)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('\'');
					}
					else
					{
						level.UpdateConsole('"');
					}
				}
				else if(wParam == VK_OEM_PERIOD)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('>');
					}
					else
					{
						level.UpdateConsole('.');
					}
				}
				else if(wParam == VK_OEM_PLUS)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('+');
					}
					else
					{
						level.UpdateConsole('=');
					}
				}
				else if(wParam == VK_OEM_COMMA)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('<');
					}
					else
					{
						level.UpdateConsole(',');
					}
				}
				else if(wParam == VK_OEM_MINUS)
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole('_');
					}
					else
					{
						level.UpdateConsole('-');
					}
				}
				else if(isalpha(uint8(wParam)))
				{
					if(keys[VK_SHIFT])
					{
						level.UpdateConsole(wParam);
					}
					else
					{
						level.UpdateConsole(tolower(wParam));
					}
				}
				else if(isdigit(uint8(wParam)))
				{
					level.UpdateConsole(wParam);
				}

			}
			else
			{
				keys[wParam] = true;
			}
			return 0;
		}
	case WM_KEYUP:
		{
			keys[wParam] = false;
			keys2[wParam] = false;
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

	level.glFont.SetScreenDimensions(level.screen.width*2, level.screen.height*2);
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
	if (!g_Screen.Open(string(OPENARENA_VERSION), level.screen.width, level.screen.height, level.screen.bpp, level.screen.fullscreen))
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
			if (keys[VK_ESCAPE])
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

		g_Screen.SwapBuffers();

		if (keys[VK_F1])
		{
			keys[VK_F1]=false;
			g_Screen.Close();
			g_Screen.fullscreen=!g_Screen.fullscreen;
			if (!g_Screen.Open("OpenArena",g_Screen.width,g_Screen.height,g_Screen.bpp,g_Screen.fullscreen))
			{
				return 0;
			}
		}
	}

	level.UnloadMap();
	g_Screen.Close();
	return (msg.wParam);
}
#endif