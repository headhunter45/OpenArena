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
#include "KeyReleaseEvent.h"
#include <cstdio>
#include "main.h"

// clang-format on

namespace OpenArena {
KeyReleaseEvent::KeyReleaseEvent(OpenArena::Keys key) {
  _key = key;
  SetEventType(KeyReleaseEventType);
}

KeyReleaseEvent::~KeyReleaseEvent() {}

OpenArena::Keys KeyReleaseEvent::GetKey() {
  return _key;
}

bool KeyReleaseEvent::KeyReleaseEventHandler::Handles(Event::EventType type) {
  if (type == Event::KeyReleaseEventType) {
    return true;
  }
  return false;
}

void KeyReleaseEvent::KeyReleaseEventHandler::HandleEvent(Event* event) {
  if (event != 0x0) {
    if (event->GetEventType() == Event::KeyReleaseEventType) {
      KeyReleaseEvent* ev = (KeyReleaseEvent*)event;
      printf("KeyReleased: %s\n", GetKeyName(ev->GetKey()));
      keys[ev->GetKey()] = false;
      keys2[ev->GetKey()] = false;
    }
  }
}

/*
void KeyReleaseEvent::KeyReleaseEventHandler::HandleEvent(Event event)
{
        if(event.GetEventType() == Event::KeyReleaseEventType)
        {
                KeyReleaseEvent ev = *((KeyReleaseEvent*)&event);
                printf("KeyReleased: %s\n", GetKeyName(ev.GetKey()));
                keys[ev.GetKey()] = false;
                keys2[ev.GetKey()] = false;
        }
}
*/

KeyReleaseEvent::KeyReleaseEventHandler::KeyReleaseEventHandler() {}

KeyReleaseEvent::KeyReleaseEventHandler::~KeyReleaseEventHandler() {}

}  // End namespace OpenArena
