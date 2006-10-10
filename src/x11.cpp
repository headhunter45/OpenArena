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
//	Module:		x11.cpp
//	Author:		Tom Hicks
//	Creation:	10-08-2006
//	LastEdit:	10-08-2006
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
#include "x11.h"
#include "main.h"
#include "version.h"

int DrawGLScene();
unsigned char TranslateButton(int keyCode);
unsigned char TranslateKey(int keyCode);
void ResizeGLScene(GLsizei width, GLsizei height);
void HandleConsoleKeyPress(OpenArena::Keys key);

bool RT()
{
	XEvent event;
	bool done = false;
	
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
	return done;
}
