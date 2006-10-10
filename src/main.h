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
#ifndef __main_h__
#define __main_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#if defined USE_GLX
#include <GL/gl.h>			// Header file for OpenGL32 library
#include <GL/glu.h>			// Header file for Glu32 library
#elif defined USE_AGL
#error unimplemented method
#elif defined USE_CGL
#error unimplemented method
#elif defined USE_WGL
#include <windows.h>
#include <GL/gl.h>			// Header file for OpenGL32 library
#include <GL/glu.h>			// Header file for Glu32 library
#endif

#include <cstdio>			// Header file for standard input/output
#include <math.h>

#include "camera.h"
#include "level.h"
#include "mygl.h"
#include "worlddefs.h"
#include "mydefs.h"
#include "screen.h"
#include "window.h"
#include "vector.h"
#pragma warning(disable: 4786)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables

extern bool		keys[256];			// Array for which keys are down now
extern bool		keys2[256];			// Array for which keys are were down already
extern bool		active;		// Is window active flag
extern bool		fullscreen;	// Is window fullscreen flag
//extern bool		showConsole = false;// Do we need to draw the console
extern OpenArena::Vec2i	g_mousePosition;


#ifdef WIN32
extern POINT mpos;
#endif
extern float lastTime;		// This will hold the time from the last frame
extern float currentTime;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Declarations

//This shouldn't need to be here
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

/*!
 * \brief
 * Write brief comment for InitControls here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for InitControls here.
 * 
 * \remarks
 * Write remarks for InitControls here.
 * 
 * \see
 * Separate items with the '|' character.
 */
void InitControls();				// Sets up player controls
/*!
 * \brief
 * Write brief comment for InitGL here.
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for InitGL here.
 * 
 * \remarks
 * Write remarks for InitGL here.
 * 
 * \see
 * Separate items with the '|' character.
 */
int InitGL();						// All setup for OpenGL goes here
/*!
 * \brief
 * Write brief comment for ReSizeGLScene here.
 * 
 * \param width
 * Description of parameter width.
 * 
 * \param height
 * Description of parameter height.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for ReSizeGLScene here.
 * 
 * \remarks
 * Write remarks for ReSizeGLScene here.
 * 
 * \see
 * Separate items with the '|' character.
 */
void ReSizeGLScene(GLsizei width, GLsizei height);	// Resize and initialize the GL window

#endif
