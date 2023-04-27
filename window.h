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
#ifndef OpenArena__window_h__
#define OpenArena__window_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "screen.h"

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

#ifdef WIN32
#endif
#include "vector.h"

namespace OpenArena {
class Window : public Screen {
 public:
  class Resizer {
   public:
    void Resize(uint32_t width, uint32_t height);
  };

  class Initializer {
   public:
    int Initialize();
  };

 public:
  Window();
  ~Window();
  void Close();
  bool Open();
  bool Open(string title,
            int width,
            int height,
            int bits,
            bool fullscreenflag);  // make that string a const char* after this works
  void SetInitializer(Initializer* initializer);
  void SetResizer(Resizer* resizer);
  void SwapBuffers();
  void Resize(uint32_t width, uint32_t height);
  Vec2i GetMousePosition();
  void SetMousePosition(Vec2i pos);

#ifdef USE_GLX
  Display* GetDisplay();
#endif
 private:
#ifdef USE_GLX
  Cursor CreateWindowedCursor();
  Cursor CreateFullscreenCursor();
  int screen;
  ::Window window;
  GLXContext hRC;
  XSetWindowAttributes attributes;
  bool doubleBuffered;
#if defined HAVE_XF86VIDMODE
  XF86VidModeModeInfo vidMode;
#endif
  int x, y;
  Display* display;
#elif defined USE_AGL
  AGLContext _aglContext;
  WindowRef _window;
  Rect _bounds;
#elif defined USE_WGL
  HGLRC glContext;
  HWND window;
  HDC deviceContext;
  HINSTANCE instance;
#endif
  Resizer* _resizer;
  Initializer* _initializer;
};
};  // namespace OpenArena

#if defined USE_GLX
static int attrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};
static int attrListDbl[] = {
    GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};
#elif defined USE_WGL
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif

#endif  // End !defined(OpenArena__window_h__)
