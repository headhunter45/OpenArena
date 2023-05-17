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
#include "myglFont.h"

// clang-format on

namespace OpenArena {

Font::Font() {
  status = 0;
  base = 0;
  texture = 0;
  screenWidth = 1;
  screenHeight = 1;
}

Font::~Font() {
  FreeFont();
}

bool Font::BuildFont(const char* texName) {
  FreeFont();

  if (LoadGLTexture(texName, texture, GL_NEAREST, GL_NEAREST)) {
    float x, y;
    base = glGenLists(256);
    glBindTexture(GL_TEXTURE_2D, texture);
    for (short i = 0; i < 256; i++) {
      x = i % 16 / 16.0f;
      y = (short)(i / 16) / 16.0f;
      glNewList(base + i, GL_COMPILE);
      glBegin(GL_QUADS);
      glTexCoord2f(x, 1 - y - 0.0625f);
      glVertex2i(0, 0);
      glTexCoord2f(x + 0.0625f, 1 - y - 0.0625f);
      glVertex2i(16, 0);
      glTexCoord2f(x + 0.0625f, 1 - y);
      glVertex2i(16, 16);
      glTexCoord2f(x, 1 - y);
      glVertex2i(0, 16);
      glEnd();
      glTranslated(16, 0, 0);
      glEndList();
    }
    status = true;
  }
  return status;
}

bool Font::FreeFont() {
  if (status) {
    glDeleteLists(base, 256);
    status = false;
  }
  return status;
}

void Font::Print(int x, int y, const char* str, unsigned int set) {
  if (status) {
    if (set > 1) set = 1;

    glBindTexture(GL_TEXTURE_2D, texture);
    // glDisable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslated(x, y, 0);
    glListBase(base - 32 + (128 * set));
    glCallLists(strlen(str), GL_BYTE, str);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    // glDisable(GL_BLEND);
    // glEnable(GL_DEPTH_TEST);
  }
}

bool Font::Loaded() {
  return status;
}

void Font::SetScreenDimensions(short x, short y) {
  screenWidth = x;
  screenHeight = y;
}

void Font::SetScreenWidth(short x) {
  screenWidth = x;
}

void Font::SetScreenHeight(short y) {
  screenHeight = y;
}

short Font::ScreenWidth() {
  return screenWidth;
}

short Font::ScreenHeight() {
  return screenHeight;
}

}  // End namespace OpenArena
