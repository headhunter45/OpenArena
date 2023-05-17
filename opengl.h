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

#ifndef OpenArena__opengl_h__
#define OpenArena__opengl_h__

// clang-format off
#include "config.h"
#ifdef _WIN32
#include <windows.h>
#endif  // End ifdef _WIN32

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif defined(_WIN32)
#include <GL/gl.h>
#include <GL/glu.h>
// link necessary libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "winmm.lib")
#endif  // defined __APPLE__

/*
#if defined USE_GLX
#include <GL/gl.h>
#include <GL/glu.h>  //maybe not necessary
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#if defined HAVE_XF86VIDMODE
#include <X11/extensions/xf86vmode.h>
#endif
#elif defined USE_AGL
#include <AGL/agl.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif defined USE_CGL
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#elif defined USE_WGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>
#endif
*/

// // define the function's prototype
// typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// // find the function and assign it to a function pointer
// GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// // function can now be called as normal
// unsigned int buffer;
// glGenBuffers(1, &buffer);
#endif  // End !defined(OpenArena__opengl_h__)
