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

#ifndef OpenArena__keys_h__
#define OpenArena__keys_h__
// clang-format off
#include "config.h"

// clang-format on

namespace OpenArena {
enum Keys {
  KEY_UNKNOWN = 0,
  KEY_BUTTON0,
  KEY_BUTTON1,
  KEY_BUTTON2,
  KEY_BUTTON3,
  KEY_BUTTON4,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN,
  KEY_SPACE,
  KEY_RETURN,
  KEY_SHIFT,
  KEY_PAUSE,
  KEY_CONTROL,
  KEY_CAPITAL,
  KEY_ESCAPE,
  KEY_PRIOR,
  KEY_NEXT,
  KEY_END,
  KEY_HOME,
  KEY_INSERT,
  KEY_DELETE,
  KEY_LWIN,
  KEY_RWIN,
  KEY_APPS,
  KEY_NUMPAD0,
  KEY_NUMPAD1,
  KEY_NUMPAD2,
  KEY_NUMPAD3,
  KEY_NUMPAD4,
  KEY_NUMPAD5,
  KEY_NUMPAD6,
  KEY_NUMPAD7,
  KEY_NUMPAD8,
  KEY_NUMPAD9,
  KEY_MULTIPLY,
  KEY_ADD,
  KEY_SUBTRACT,
  KEY_DIVIDE,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_NUMLOCK,
  KEY_SCROLL,
  KEY_SEPARATOR,
  KEY_OEM_1,
  KEY_OEM_2,
  KEY_OEM_3,
  KEY_OEM_4,
  KEY_OEM_5,
  KEY_OEM_6,
  KEY_OEM_7,
  KEY_OEM_PERIOD,
  KEY_OEM_PLUS,
  KEY_OEM_MINUS,
  KEY_OEM_COMMA,
  KEY_BACK,
  KEY_TAB,
  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_ALT_L,
  KEY_ALT_R,
  KEY_ENTER,
  KEY_COMMAND,
  KEY_OPTION
};

const Keys KEY_LBUTTON = KEY_BUTTON0;
const Keys KEY_RBUTTON = KEY_BUTTON1;
const Keys KEY_MBUTTON = KEY_BUTTON2;
char KeyToASCII(Keys key, bool shift);
const char* GetKeyName(Keys key);
OpenArena::Keys GetKey(const char* keyName);

}  // End namespace OpenArena
#endif  // End !defined(OpenArena__keys_h__)
