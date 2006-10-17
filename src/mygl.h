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
#ifndef __MYGL_H__
#define __MYGL_H__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#if defined USE_GLX
#include <GL/gl.h>
#include <GL/glu.h>
#elif defined USE_AGL
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
//#error unimplemented method
#elif defined USE_CGL
#error unimplemented method
#elif defined USE_WGL
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>
#include "datatypes.h"
#include "screen.h"
#include "tga.h"
#include "bmp.h"
#include "strmanip.h"
#include "window.h"

using namespace std;

#ifdef WIN32
//These this is windows specific
static HINSTANCE	hInstance;			// Application instance
#endif
extern OpenArena::Window* g_Screen;
//This doesn't need to be here I think
//int InitGL(GLvoid);
namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for LoadGLTexture here.
	 * 
	 * \param 
	 * Description of parameter .
	 * 
	 * \param 
	 * Description of parameter .
	 * 
	 * \param 
	 * Description of parameter .
	 * 
	 * \param 
	 * Description of parameter .
	 * 
	 * \returns
	 * Write description of return value here.
	 * 
	 * \throws <exception class>
	 * Description of criteria for throwing this exception.
	 * 
	 * Write detailed description for LoadGLTexture here.
	 * 
	 * \remarks
	 * Write remarks for LoadGLTexture here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	bool LoadGLTexture(string , GLuint&, GLuint = GL_LINEAR, GLuint = GL_LINEAR);
	/*!
	 * \brief
	 * Write brief comment for FreeGLTexture here.
	 * 
	 * \param 
	 * Description of parameter .
	 * 
	 * \throws <exception class>
	 * Description of criteria for throwing this exception.
	 * 
	 * Write detailed description for FreeGLTexture here.
	 * 
	 * \remarks
	 * Write remarks for FreeGLTexture here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	void FreeGLTexture(GLuint&);
};
#endif
