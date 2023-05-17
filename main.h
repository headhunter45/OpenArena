/***************************************************************************
 *   Copyright (C) 2001-2023 by Tom Hicks                                  *
 *   headhunter3@gmail.com                                                 *
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

#ifndef OpenArena__main_h__
#define OpenArena__main_h__
// clang-format off
#include "config.h"

#if defined USE_GLX
#include <GL/gl.h>   // Header file for OpenGL32 library
#include <GL/glu.h>  // Header file for Glu32 library
#elif defined USE_AGL
#include "mygl.h"
#elif defined USE_CGL
#error unimplemented method
#elif defined USE_WGL
#include <windows.h>
#include <GL/gl.h>   // Header file for OpenGL32 library
#include <GL/glu.h>  // Header file for Glu32 library
#endif

#include <math.h>

#include <cstdio>  // Header file for standard input/output

#include "camera.h"
#include "level.h"
#include "mydefs.h"
#include "mygl.h"
#include "screen.h"
#include "vector.h"
#include "window.h"
#include "worlddefs.h"
// clang-format on

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables

extern bool keys[256];   // Array for which keys are down now
extern bool keys2[256];  // Array for which keys are were down already
extern bool active;      // Is window active flag
extern bool fullscreen;  // Is window fullscreen flag
// extern bool		showConsole = false;// Do we need to draw the console
extern OpenArena::Vec2i g_mousePosition;

#ifdef WIN32
extern POINT mpos;
#endif                  // OpenArena__main_h__
extern float lastTime;  // This will hold the time from the last frame
extern float currentTime;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Declarations

// This shouldn't need to be here
// LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

void InitControls();                                // Sets up player controls
int InitGL();                                       // All setup for OpenGL goes here
void ReSizeGLScene(GLsizei width, GLsizei height);  // Resize and initialize the GL window
int DrawGLScene(OpenArena::Level* level);

#endif  // End !defined(OpenArena__main_h__)
