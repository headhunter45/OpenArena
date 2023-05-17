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

// clang-format off
#include "screen.h"

// clang-format on

namespace OpenArena {
namespace {
using std::string;
}  // End namespace

Screen::Screen() {
  _width = 640;
  _height = 480;
  _colorDepth = 16;
  _fullscreen = false;
  _name = "";
}

int Screen::GetWidth() {
  return _width;
}

int Screen::GetHeight() {
  return _height;
}

int Screen::GetColorDepth() {
  return _colorDepth;
}

bool Screen::GetFullscreen() {
  return _fullscreen;
}

const char* Screen::GetName() {
  return _name.c_str();
}

void Screen::SetWidth(int width) {
  _width = width;
}

void Screen::SetHeight(int height) {
  _height = height;
}

void Screen::Resize(int width, int height) {
  _width = width;
  _height = height;
}

void Screen::SetColorDepth(int colorDepth) {
  _colorDepth = colorDepth;
}

void Screen::SetFullscreen(bool status) {
  _fullscreen = status;
}

void Screen::ToggleFullscreen() {
  _fullscreen = !_fullscreen;
}

void Screen::SetName(const char* name) {
  _name = name;
}

void Screen::SetName(string name) {
  _name = name;
}
}  // End namespace OpenArena
