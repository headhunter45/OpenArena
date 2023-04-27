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
#ifndef OpenArena__ctrls_h__
#define OpenArena__ctrls_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif
#include <iostream>
#include <string>

#include "keys.h"

namespace OpenArena {
class ControlScheme {
 public:
  enum Action {
    ACTION_NONE = 0,
    ACTION_FORWARD,
    ACTION_BACKWARD,
    ACTION_LOOKLEFT,
    ACTION_LOOKRIGHT,
    ACTION_LOOKUP,
    ACTION_LOOKDOWN,
    ACTION_MOVELEFT,
    ACTION_MOVERIGHT,
    ACTION_MOVEUP,
    ACTION_MOVEDOWN,
    ACTION_ROLLLEFT,
    ACTION_ROLLRIGHT,
    ACTION_FIREPRIMARY,
    ACTION_FIRESECONDARY,
    ACTION_WEAPONNEXT,
    ACTION_WEAPONPREV,
    ACTION_TOGGLE_LIGHTS,
    ACTION_TOGGLE_FPS,
    ACTION_TOGGLE_CONSOLE,
    ACTION_TOGGLE_MOUSELOOK,
    ACTION_QUICKMOUSELOOK,
    NUM_ACTIONS
  };

  void LoadDefaultControlScheme();
  void UnBindAll();
  void UnBind(OpenArena::Keys key);
  void Bind(OpenArena::Keys key, Action action);
  void WriteToStream(std::ostream& output);
  static Action GetAction(const char* actionName);
  static const char* GetActionName(Action action);
  bool IsBound(OpenArena::Keys key, Action action);

 private:
  std::string ActionName(Action action);
  Action keyActions[256];
};
}  // End namespace OpenArena

#endif  // End !defined(OpenArena__ctrls_h__)
