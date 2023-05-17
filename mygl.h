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

#ifndef OpenArena__mygl_h__
#define OpenArena__mygl_h__
// clang-format off
#include "config.h"
#include "opengl.h"
#include "window.h"
// clang-format on

#ifdef WIN32
// These this is windows specific
static HINSTANCE hInstance;  // Application instance
#endif

namespace OpenArena {
// TODO: Move this to behidden in mygl.cpp.
extern OpenArena::Window* g_Screen;

bool LoadGLTexture(std::string, GLuint&, GLuint = GL_LINEAR, GLuint = GL_LINEAR);
void FreeGLTexture(GLuint&);
};      // namespace OpenArena
#endif  // !defined(OpenArena__mygl_h__)
