/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks   *
 *   tomhicks@cse.buffalo.edu   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
////////////////////////////////////////////////////////////////////////////////
//
//	Module:		macosx.cpp
//	Author:		Tom Hicks
//	Creation:	03-11-2006
//	LastEdit:	03-11-2006
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
#ifdef __APPLE__
#include "main.h"
#include "version.h"
#include "x11.h"
//include necessary header files
using namespace std;
unsigned char TranslateKey(int keyCode);
unsigned char TranslateButton(int keyCode);

#if defined USE_GLX
//void InitControls();
void HandleConsoleKeyPress(OpenArena::Keys key);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions

int DrawGLScene()
{
	//The context is somehow different if this call is inside the RT function
	level.Render();

	RT();
	
	return true;
}

//
//int InitGL(GLvoid)
//	Purpose:
//		To do all required setup before creating an OpenGL window
///*
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

	level.glFont.SetScreenDimensions(level.screen.GetWidth()*2, level.screen.GetHeight()*2);

	if(level.nextLevel == "")
	{
		level.LoadMap("intro.map");
	}
	else
	{
		level.LoadMap();
	}

	//Hack for now
	if(level.screen.GetColorDepth() == 32)
	{
		level.screen.SetColorDepth(24);
	}

//	g_Screen.SetInitializer(new OpenArena::Window::Initializer());
//	g_Screen.SetResizer(new OpenArena::Window::Resizer());

	if(!g_Screen.Open(OPENARENA_VERSION, level.screen.GetWidth(), level.screen.GetHeight(), level.screen.GetColorDepth(), level.screen.GetFullscreen()))
	{
		return 1;
	}
	
	level.SetWindow(&g_Screen);
	
	level.LoadGLTextures();

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
				if((event.xconfigure.width != g_Screen.GetWidth()) || (event.xconfigure.height != g_Screen.GetHeight()))
				{
					g_Screen.SetWidth(event.xconfigure.width);
					g_Screen.SetHeight(event.xconfigure.height);
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
				if(level.showConsole)
				{
					HandleConsoleKeyPress((OpenArena::Keys)TranslateKey(XLookupKeysym(&event.xkey, 0)));
				}
				else
				{
					keys[TranslateKey(XLookupKeysym(&event.xkey, 0))] = true;
				}
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
		}	//End Equivalent of WNDPROC
		
		if(active)
		{
			if(keys[OpenArena::KEY_ESCAPE])
			{
				done = true;
			}
			else if(keys[OpenArena::KEY_F1])
			{
				g_Screen.Close();
				g_Screen.ToggleFullscreen();
				g_Screen.Open();
			}
			else
			{
				level.defaultPlayer[0].camera.Update();
				if(!level.showConsole)
				{
					if(level.mlook)
					{
						using OpenArena::Vec2i;
						Vec2i middleOfScreen = Vec2i(g_Screen.GetWidth()/2, g_Screen.GetHeight()/2);
						Vec2i mousePosition = g_Screen.GetMousePosition();
						if(mousePosition != middleOfScreen)
						{
							//Vec2i mouseDelta = mousePosition - middleOfScreen;
							Vec2i mouseDelta = middleOfScreen - mousePosition;
							g_Screen.SetMousePosition(middleOfScreen);
							const float MOUSE_SENSITIVITY_HORIZONTAL = 0.005;
							const float MOUSE_SENSITIVITY_VERTICAL = 0.005;
							float horizontalAngle = mouseDelta.x * MOUSE_SENSITIVITY_HORIZONTAL;
							float verticalAngle = mouseDelta.y * MOUSE_SENSITIVITY_VERTICAL;
							level.defaultPlayer[0].camera.RotateHorizontal(horizontalAngle);
							level.defaultPlayer[0].camera.RotateVertical(verticalAngle);
						}
					}
					else
					{
//						SetMousePosition(g_Screen.width/2, g_Screen.height/2);//Shit this may be windows specific
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
			g_Screen.ToggleFullscreen();
			if(!g_Screen.Open(OPENARENA_VERSION, level.screen.GetWidth(), level.screen.GetHeight(), level.screen.GetColorDepth(), level.screen.GetFullscreen()))
			{
				return 1;
			}
		}
		
	}
	level.UnloadMap();
	g_Screen.Close();
	exit(0);
}
/**/

#elif defined USE_AGL
#error
#elif defined USE_CGL
#error
#endif

bool keys[256] = {0};			// Array for which keys are down now
bool keys2[256] = {0};			// Array for which keys are were down already
bool active = true;		// Is window active flag
bool fullscreen = false;	// Is window fullscreen flag
//bool showConsole = false;// Do we need to draw the console
OpenArena::Vec2i g_mousePosition;
float lastTime = 0.0f;		// This will hold the time from the last frame
float currentTime;

#endif
