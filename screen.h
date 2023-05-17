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

#ifndef OpenArena__screen_h__
#define OpenArena__screen_h__
// clang-format off
#include "config.h"
#include <string>

// clang-format on

namespace OpenArena {
class Screen {
 public:
  Screen();
  int GetWidth();
  int GetHeight();
  int GetColorDepth();
  bool GetFullscreen();
  const char* GetName();
  void SetWidth(int);
  void SetHeight(int);
  void Resize(int, int);
  void SetColorDepth(int);
  void SetFullscreen(bool);
  void ToggleFullscreen();
  void SetName(const char*);
  void SetName(std::string);

 protected:
  short _width;
  short _height;
  char _colorDepth;
  bool _fullscreen;
  std::string _name;
};
}  // End namespace OpenArena
#endif  // End !defined(OpenArena__screen_h__)
