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
#include "ctrls.h"
#include "strmanip.h"
// clang-foramt on

namespace OpenArena {
  namespace {
    using std::endl;
    using std::ostream;
    using std::string;
  } // End namespace

void ControlScheme::LoadDefaultControlScheme() {
  UnBindAll();
  Bind(OpenArena::KEY_LBUTTON, ACTION_FORWARD);
  Bind(OpenArena::KEY_RBUTTON, ACTION_BACKWARD);
  Bind(OpenArena::KEY_LEFT, ACTION_LOOKLEFT);
  Bind(OpenArena::KEY_RIGHT, ACTION_LOOKRIGHT);
  Bind(OpenArena::KEY_UP, ACTION_LOOKUP);
  Bind(OpenArena::KEY_DOWN, ACTION_LOOKDOWN);
  Bind(OpenArena::KEY_S, ACTION_MOVELEFT);
  Bind(OpenArena::KEY_D, ACTION_MOVERIGHT);
  Bind(OpenArena::KEY_SPACE, ACTION_MOVEUP);
  Bind(OpenArena::KEY_A, ACTION_MOVEDOWN);
  Bind(OpenArena::KEY_F, ACTION_FIREPRIMARY);
  Bind(OpenArena::KEY_G, ACTION_FIRESECONDARY);
  Bind(OpenArena::KEY_T, ACTION_WEAPONNEXT);
  Bind(OpenArena::KEY_R, ACTION_WEAPONPREV);
  Bind(OpenArena::KEY_L, ACTION_TOGGLE_LIGHTS);
  Bind(OpenArena::KEY_P, ACTION_TOGGLE_FPS);
  Bind(OpenArena::KEY_OEM_3, ACTION_TOGGLE_CONSOLE);
  Bind(OpenArena::KEY_M, ACTION_TOGGLE_MOUSELOOK);
  Bind(OpenArena::KEY_Q, ACTION_QUICKMOUSELOOK);
  Bind(OpenArena::KEY_W, ACTION_ROLLLEFT);
  Bind(OpenArena::KEY_E, ACTION_ROLLRIGHT);
}

void ControlScheme::UnBindAll() {
  OpenArena::Keys key;
  for (key = (OpenArena::Keys)0; key < (OpenArena::Keys)256; key = (OpenArena::Keys)(key + 1)) {
    UnBind(key);
  }
}

void ControlScheme::UnBind(OpenArena::Keys key) {
  keyActions[key] = ACTION_NONE;
}

void ControlScheme::Bind(OpenArena::Keys key, Action action) {
  keyActions[key] = action;
}

void ControlScheme::WriteToStream(std::ostream& output) {
  // output << " bind " << action << keyname << endl;
  OpenArena::Keys key;
  for (key = (OpenArena::Keys)0; key < (OpenArena::Keys)256; key = (OpenArena::Keys)(key + 1)) {
    if (keyActions[key] != ACTION_NONE) {
      output << " bind " << ActionName(keyActions[key]) << GetKeyName(key) << endl;
    }
  }
}

ControlScheme::Action ControlScheme::GetAction(const char* actionName) {
  string str = actionName;
  str = tolower(str);
  if (str == "none") {
    return ACTION_NONE;
  } else if (str == "forward") {
    return ACTION_FORWARD;
  } else if (str == "backward") {
    return ACTION_BACKWARD;
  } else if (str == "lookleft") {
    return ACTION_LOOKLEFT;
  } else if (str == "lookright") {
    return ACTION_LOOKRIGHT;
  } else if (str == "lookup") {
    return ACTION_LOOKUP;
  } else if (str == "lookdown") {
    return ACTION_LOOKDOWN;
  } else if (str == "moveleft") {
    return ACTION_MOVELEFT;
  } else if (str == "moveright") {
    return ACTION_MOVERIGHT;
  } else if (str == "moveup") {
    return ACTION_MOVEUP;
  } else if (str == "movedown") {
    return ACTION_MOVEDOWN;
  } else if (str == "rollleft") {
    return ACTION_ROLLLEFT;
  } else if (str == "rollright") {
    return ACTION_ROLLRIGHT;
  } else if (str == "fireprimary") {
    return ACTION_FIREPRIMARY;
  } else if (str == "firesecondary") {
    return ACTION_FIRESECONDARY;
  } else if (str == "weaponnext") {
    return ACTION_WEAPONNEXT;
  } else if (str == "weaponprev") {
    return ACTION_WEAPONPREV;
  } else if (str == "togglelights") {
    return ACTION_TOGGLE_LIGHTS;
  } else if (str == "togglefps") {
    return ACTION_TOGGLE_FPS;
  } else if (str == "toggleconsole") {
    return ACTION_TOGGLE_CONSOLE;
  } else if (str == "togglemouselook") {
    return ACTION_TOGGLE_MOUSELOOK;
  } else if (str == "quickmouselook") {
    return ACTION_QUICKMOUSELOOK;
  } else {
    return ACTION_NONE;
  }
}

string ControlScheme::ActionName(Action action) {
  switch (action) {
    case ACTION_NONE:
      return "none";
    case ACTION_FORWARD:
      return "forward";
    case ACTION_BACKWARD:
      return "backward";
    case ACTION_LOOKLEFT:
      return "lookleft";
    case ACTION_LOOKRIGHT:
      return "lookright";
    case ACTION_LOOKUP:
      return "lookup";
    case ACTION_LOOKDOWN:
      return "lookdown";
    case ACTION_MOVELEFT:
      return "moveleft";
    case ACTION_MOVERIGHT:
      return "moveright";
    case ACTION_MOVEUP:
      return "moveup";
    case ACTION_MOVEDOWN:
      return "movedown";
    case ACTION_ROLLLEFT:
      return "rollleft";
    case ACTION_ROLLRIGHT:
      return "rollright";
    case ACTION_FIREPRIMARY:
      return "fireprimary";
    case ACTION_FIRESECONDARY:
      return "firesecondary";
    case ACTION_WEAPONNEXT:
      return "weaponnext";
    case ACTION_WEAPONPREV:
      return "weaponprev";
    case ACTION_TOGGLE_LIGHTS:
      return "togglelights";
    case ACTION_TOGGLE_FPS:
      return "togglefps";
    case ACTION_TOGGLE_CONSOLE:
      return "toggleconsole";
    case ACTION_TOGGLE_MOUSELOOK:
      return "togglemouselook";
    case ACTION_QUICKMOUSELOOK:
      return "quickmouselook";
    default:
      return "unknown";
  };
}

bool ControlScheme::IsBound(OpenArena::Keys key, Action action) {
  if (keyActions[key] == action) {
    return true;
  }

  return false;
}

ControlScheme::Action ControlScheme::GetAction(OpenArena::Keys key) {
  return keyActions[key];
}

ControlScheme::ControlScheme(){
  UnBindAll();
}
}  // End namespace OpenArena
