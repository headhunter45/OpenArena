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

// clang-format off
#include "config.h"
#include "opengl.h"
#include "screen.h"
#include "vector.h"

// clang-format on

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
  virtual ~Window();
  virtual void Close();
  virtual bool Open();
  virtual bool Open(std::string title, int width, int height, int bits,
                    bool fullscreenflag);  // make that string a const char* after this works
  virtual void SetInitializer(Initializer* initializer);
  virtual void SetResizer(Resizer* resizer);
  virtual void SwapBuffers();
  virtual void Resize(uint32_t width, uint32_t height);
  virtual Vec2i GetMousePosition();
  virtual void SetMousePosition(Vec2i pos);

 private:
#ifdef USE_WGL
  // TODO: move this to opengl/window
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
static int attrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4,   GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE,
                            4,        GLX_DEPTH_SIZE,   16,           None};
#elif defined USE_WGL
// TODO: Move this to opengl/window.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif

#endif  // End !defined(OpenArena__window_h__)
