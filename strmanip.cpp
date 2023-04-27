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
#include "strmanip.h"

#include <cctype>

#include "keys.h"

bool Truth(std::string str) {
  if (toupper(str[0]) == 'T' || str[0] == '1')
    return true;
  else
    return false;
}

int Integer(std::string str) {
  int last = str.length() - 1;
  int number = 0;

  for (int x = last; x >= 0; x--) {
    switch (str[x]) {
      case '1':
        number += (int)pow(10.0, last - x);
        break;
      case '2':
        number += 2 * (int)pow(10.0, last - x);
        break;
      case '3':
        number += 3 * (int)pow(10.0, last - x);
        break;
      case '4':
        number += 4 * (int)pow(10.0, last - x);
        break;
      case '5':
        number += 5 * (int)pow(10.0, last - x);
        break;
      case '6':
        number += 6 * (int)pow(10.0, last - x);
        break;
      case '7':
        number += 7 * (int)pow(10.0, last - x);
        break;
      case '8':
        number += 8 * (int)pow(10.0, last - x);
        break;
      case '9':
        number += 9 * (int)pow(10.0, last - x);
    }
  }
  return number;
}

float Floating(std::string str) {
  // this doesn't work right yet so use atof for now

  int last = str.length() - 1;
  float number = 0.0f;
  bool period = false;

  for (int x = last; x >= 0; x--) {
    switch (str[x]) {
      case '1':
        number += (float)pow(10.0, last - x);
        break;
      case '2':
        number += 2 * (float)pow(10.0, last - x);
        break;
      case '3':
        number += 3 * (float)pow(10.0, last - x);
        break;
      case '4':
        number += 4 * (float)pow(10.0, last - x);
        break;
      case '5':
        number += 5 * (float)pow(10.0, last - x);
        break;
      case '6':
        number += 6 * (float)pow(10.0, last - x);
        break;
      case '7':
        number += 7 * (float)pow(10.0, last - x);
        break;
      case '8':
        number += 8 * (float)pow(10.0, last - x);
        break;
      case '9':
        number += 9 * (float)pow(10.0, last - x);
        break;
      case '.':
        if (!period) {
          number *= (float)pow(10.0, -(last - x));
          last -= (x + 1);
          period = true;
        } else
          return number;
    }
  }

  if (str[0] == '-')
    return -number;
  else
    return number;
}

string KeyString(uint8_t key) {
  switch (key) {
    case OpenArena::KEY_LBUTTON:
      return "mouse1";
    case OpenArena::KEY_RBUTTON:
      return "mouse2";
    case OpenArena::KEY_MBUTTON:
      return "mouse3";
    case OpenArena::KEY_TAB:
      return "tab";
    case OpenArena::KEY_RETURN:
      return "enter";
    case OpenArena::KEY_SHIFT:
      return "shift";
    case OpenArena::KEY_CONTROL:
      return "control";
    case OpenArena::KEY_PAUSE:
      return "pause";
    case OpenArena::KEY_CAPITAL:
      return "capslock";
    case OpenArena::KEY_ESCAPE:
      return "esc";
    case OpenArena::KEY_SPACE:
      return "space";
    case OpenArena::KEY_PRIOR:
      return "pageup";
    case OpenArena::KEY_NEXT:
      return "pagedown";
    case OpenArena::KEY_END:
      return "end";
    case OpenArena::KEY_HOME:
      return "home";
    case OpenArena::KEY_LEFT:
      return "left";
    case OpenArena::KEY_UP:
      return "up";
    case OpenArena::KEY_RIGHT:
      return "right";
    case OpenArena::KEY_DOWN:
      return "down";
    case OpenArena::KEY_INSERT:
      return "insert";
    case OpenArena::KEY_DELETE:
      return "delete";
    case OpenArena::KEY_LWIN:
      return "lwin";
    case OpenArena::KEY_RWIN:
      return "rwin";
    case OpenArena::KEY_APPS:
      return "apps";
    case OpenArena::KEY_NUMPAD0:
      return "numpad0";
    case OpenArena::KEY_NUMPAD1:
      return "numpad1";
    case OpenArena::KEY_NUMPAD2:
      return "numpad2";
    case OpenArena::KEY_NUMPAD3:
      return "numpad3";
    case OpenArena::KEY_NUMPAD4:
      return "numpad4";
    case OpenArena::KEY_NUMPAD5:
      return "numpad5";
    case OpenArena::KEY_NUMPAD6:
      return "numpad6";
    case OpenArena::KEY_NUMPAD7:
      return "numpad7";
    case OpenArena::KEY_NUMPAD8:
      return "numpad8";
    case OpenArena::KEY_NUMPAD9:
      return "numpad9";
    case OpenArena::KEY_MULTIPLY:
      return "numpad*";
    case OpenArena::KEY_ADD:
      return "numpad+";
    case OpenArena::KEY_SUBTRACT:
      return "numpad-";
    case OpenArena::KEY_DIVIDE:
      return "numpad/";
    case OpenArena::KEY_F1:
      return "f1";
    case OpenArena::KEY_F2:
      return "f2";
    case OpenArena::KEY_F3:
      return "f3";
    case OpenArena::KEY_F4:
      return "f4";
    case OpenArena::KEY_F5:
      return "f5";
    case OpenArena::KEY_F6:
      return "f6";
    case OpenArena::KEY_F7:
      return "f7";
    case OpenArena::KEY_F8:
      return "f8";
    case OpenArena::KEY_F9:
      return "f9";
    case OpenArena::KEY_F10:
      return "f10";
    case OpenArena::KEY_F11:
      return "f11";
    case OpenArena::KEY_F12:
      return "f2";
    case OpenArena::KEY_NUMLOCK:
      return "numlock";
    case OpenArena::KEY_SCROLL:
      return "scroll";
    case OpenArena::KEY_SEPARATOR:
      return "separator";
    default:
      return "null";
  };
}

string Right(string str, uint32_t len) {
  return str.substr(str.length() - len, len);
}

string Left(string str, uint32_t len) {
  return str.substr(0, len);
}

string tolower(string str) {
  for (uint32_t i = 0; i < str.length(); i++) str[i] = tolower(str[i]);

  return str;
}

string toupper(string str) {
  for (uint32_t i = 0; i < str.length(); i++) str[i] = toupper(str[i]);

  return str;
}

string word(string str, uint32_t wordNum) {
  ///////////////
  // stopped here
  ///////////////
  uint32_t start = 0;
  uint32_t length = 0;
  uint32_t maxLength = str.length();
  if (str.length() > 0) {
    if (wordNum < 1) {
      while (isspace(str[start])) ++start;

      while (!isspace(str[++length]) && length < maxLength)
        ;

      if (length < maxLength || isspace(str[length])) {
        if (length > 0) {
          length--;
        }
      }
      return str.substr(start, length);
    } else {
      while (isspace(str[start])) ++start;

      for (uint32_t i = 0; i < wordNum; i++) {
        while (start < maxLength && !isspace(str[start]))  // && start <= maxLength)
          ++start;
        while (start < maxLength && isspace(str[start])) ++start;
      }

      ;

      while ((start + length) < maxLength && !isspace(str[start + length])) ++length;

      return str.substr(start, length);
    }
  } else {
    return "";
  }
}
