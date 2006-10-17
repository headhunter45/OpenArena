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
#ifndef __x11_h__
#define __x11_h__
#if defined HAVE_CONFIG_H
#include "config.h"
#endif
 
#if defined USE_GLX
#include "mygl.h"
#include "EventManager.h"
#include "level.h"

int DrawGLScene();
OpenArena::Keys TranslateButton(int keyCode);
OpenArena::Keys TranslateKey(int keyCode);
void ResizeGLScene(GLsizei width, GLsizei height);
void HandleConsoleKeyPress(OpenArena::Keys key);
int DrawGLScene(OpenArena::Level* level);
int InitGL(OpenArena::Level* level);
void HandleConsoleKeyPress(OpenArena::Keys key, OpenArena::Level* level);
#endif /* USE_GLX */
#endif /* __x11_h__ */
