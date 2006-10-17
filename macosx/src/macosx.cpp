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
#include "EventManager.h"
#include "Events/DrawEvent.h"
#include "Events/KeyPressEvent.h"
#include "Events/KeyReleaseEvent.h"
#include "x11.h"
//include necessary header files
using namespace std;

bool g_done = false;
class KeyPressEventHandler: public OpenArena::Events::KeyPressEvent::KeyPressEventHandler
{
private:
public:
	KeyPressEventHandler()
	{
	}
	
	virtual void HandleEvent(OpenArena::Events::Event* event)
	{
		OpenArena::Events::KeyPressEvent* ev = (OpenArena::Events::KeyPressEvent*) event; 
		switch (ev->GetKey())
		{
		case OpenArena::KEY_ESCAPE:
			g_done = true;
			break;
		
		default:
			break;		
		};
	}
};

int DrawGLScene(OpenArena::Level* level)
{
	//The context is somehow different if this call is inside the RT function
	level->Render();

	g_Screen->SwapBuffers();
	
	return true;
}

#if defined USE_GLX
//void InitControls();
void HandleConsoleKeyPress(OpenArena::Keys key);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions

void ProcessCommandLineArgs(int argc, char** argv, OpenArena::Level* level)
{
	string commandLine = "";
	int i;
	for(i=1; i<argc; i++)
	{
		commandLine = commandLine + " " + argv[i];
	}
	level->ParseCmds(commandLine.c_str());	
}

int main(int argc, char** argv)
{
	g_Screen = new OpenArena::Window();
	OpenArena::EventManager* em = new OpenArena::EventManager();
	OpenArena::Level* level = new OpenArena::Level(em);
	OpenArena::Events::DrawEvent::DrawEventHandler* _drawEventHandler = new OpenArena::Events::DrawEvent::DrawEventHandler(level);
	KeyPressEventHandler* _keyPressEventHandler = new KeyPressEventHandler();
	OpenArena::Events::KeyReleaseEvent::KeyReleaseEventHandler* _keyReleaseEventHandler = new OpenArena::Events::KeyReleaseEvent::KeyReleaseEventHandler();
	em->RegisterEventHandler(_drawEventHandler);
	em->RegisterEventHandler(_keyPressEventHandler);
	em->RegisterEventHandler(_keyReleaseEventHandler);
	
	XEvent event;
	OpenArena::Events::Event* ev;
	
	ProcessCommandLineArgs(argc, argv, level);

	if (!level->LoadConfig("my.cfg"))
		level->LoadConfig();

	level->glFont.SetScreenDimensions(level->screen.GetWidth()*2, level->screen.GetHeight()*2);

	if(level->nextLevel == "")
	{
		level->LoadMap("intro.map");
	}
	else
	{
		level->LoadMap();
	}
	
	//Hack for now X11 no like 32 bit depth
	if(level->screen.GetColorDepth() == 32)
	{
		level->screen.SetColorDepth(24);
	}

	if(!g_Screen->Open(OPENARENA_VERSION, level->screen.GetWidth(), level->screen.GetHeight(), level->screen.GetColorDepth(), level->screen.GetFullscreen()))
	{
		return 1;
	}
			
	level->SetWindow(g_Screen);
	
	level->LoadGLTextures();

	while(!g_done)
	{
		while(XPending(g_Screen->GetDisplay()) > 0)
		{
			OpenArena::Events::Event* ev = 0x0;
			//Equivalent of WNDPROC
			XNextEvent(g_Screen->GetDisplay(), &event);
			switch(event.type)
			{
			case Expose:
				if(event.xexpose.count != 0)
				{
					break;
				}
				
				em->SendEvent(new OpenArena::Events::DrawEvent());
				break;
			case ConfigureNotify:
				if((event.xconfigure.width != g_Screen->GetWidth()) || (event.xconfigure.height != g_Screen->GetHeight()))
				{
					g_Screen->SetWidth(event.xconfigure.width);
					g_Screen->SetHeight(event.xconfigure.height);
					ResizeGLScene(event.xconfigure.width, event.xconfigure.height);
					
					//em->SendEvent(new ResizeWindowEvent(event.xconfigure.width, event.xconfigure.width);
				}
				break;
			case ButtonPress:
				em->SendEvent(new OpenArena::Events::KeyPressEvent(TranslateButton(event.xbutton.button)));
				break;
			case ButtonRelease:
				em->SendEvent(new OpenArena::Events::KeyReleaseEvent(TranslateButton(event.xbutton.button)));
				break;
			case KeyPress:
				em->SendEvent(new OpenArena::Events::KeyPressEvent((OpenArena::Keys)TranslateKey(XLookupKeysym(&event.xkey, 0))));
	/*
	 			if(level->showConsole)
				{
					HandleConsoleKeyPress((OpenArena::Keys)TranslateKey(XLookupKeysym(&event.xkey, 0)));
				}
				else
				{
					keys[TranslateKey(XLookupKeysym(&event.xkey, 0))] = true;
				}
	*/ 
 				break;
			case KeyRelease:
				em->SendEvent(new OpenArena::Events::KeyReleaseEvent((OpenArena::Keys)TranslateKey(XLookupKeysym(&event.xkey, 0))));
//				keys[TranslateKey(XLookupKeysym(&event.xkey, 0))] = false;
//				keys2[TranslateKey(XLookupKeysym(&event.xkey, 0))] = false;
				break;
			case ClientMessage:
				if(*XGetAtomName(g_Screen->GetDisplay(), event.xclient.message_type) == *"WM_PROTOCOLS")
				{
					printf("Exiting sanely...\n");
					g_done = true;
				}
				break;
			default:
				break;
			}
		}	//End Equivalent of WNDPROC
		
		/*
		if(active)
		{
			if(keys[OpenArena::KEY_ESCAPE])
			{
				g_done = true;
			}
			else if(keys[OpenArena::KEY_F1])
			{
				g_Screen->Close();
				g_Screen->ToggleFullscreen();
				g_Screen->Open();
			}
			else
			{
				level->defaultPlayer[0].camera.Update();
			}
		}
		*/
		
		em->SendEvent(new OpenArena::Events::DrawEvent());

		if(keys[OpenArena::KEY_F1])
		{
			keys[OpenArena::KEY_F1] = false;
			g_Screen->Close();
			g_Screen->ToggleFullscreen();
			if(!g_Screen->Open(OPENARENA_VERSION, level->screen.GetWidth(), level->screen.GetHeight(), level->screen.GetColorDepth(), level->screen.GetFullscreen()))
			{
				return 1;
			}
		}		
	}
	level->UnloadMap();
	g_Screen->Close();
	exit(0);
}

#elif defined USE_AGL
int main(int argc, char** argv)
{
	g_Screen = new OpenArena::Window();
	OpenArena::Events::DrawEvent::DrawEventHandler* _drawEventHandler = new OpenArena::Events::DrawEvent::DrawEventHandler();
	OpenArena::Events::KeyPressEvent::KeyPressEventHandler* _keyPressEventHandler = new OpenArena::Events::KeyPressEvent::KeyPressEventHandler();
	OpenArena::Events::KeyReleaseEvent::KeyReleaseEventHandler* _keyReleaseEventHandler = new OpenArena::Events::KeyReleaseEvent::KeyReleaseEventHandler();
	OpenArena::EventManager* em = new OpenArena::EventManager();
	em->RegisterEventHandler(_drawEventHandler);
	em->RegisterEventHandler(_keyPressEventHandler);
	em->RegisterEventHandler(_keyReleaseEventHandler);
	
//	ProcessCommandLineArgs(argc, argv);

//	InitControls();
	
	level->glFont.SetScreenDimensions(level->screen.GetWidth()*2, level->screen.GetHeight()*2);

	if(level->nextLevel == "")
	{
		level->LoadMap("intro.map");
	}
	else
	{
		level->LoadMap();
	}
	
	//Hack for now X11 no like 32 bit depth
	if(level->screen.GetColorDepth() == 32)
	{
		level->screen.SetColorDepth(24);
	}

	if(!g_Screen->Open(OPENARENA_VERSION, level->screen.GetWidth(), level->screen.GetHeight(), level->screen.GetColorDepth(), level->screen.GetFullscreen()))
	{
		return 1;
	}
			
	level->SetWindow(g_Screen);
	
	level->LoadGLTextures();

	RunApplicationEventLoop();
	
}
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

