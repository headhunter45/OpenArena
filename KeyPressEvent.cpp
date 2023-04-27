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
#include "KeyPressEvent.h"

#include <cstdio>

#include "main.h"

namespace OpenArena {
KeyPressEvent::KeyPressEvent(OpenArena::Keys key) {
  printf("KeyPressEvent created");
  _key = key;
  SetEventType(KeyPressEventType);
}

KeyPressEvent::~KeyPressEvent() {}

OpenArena::Keys KeyPressEvent::GetKey() {
  return _key;
}

bool KeyPressEvent::KeyPressEventHandler::Handles(Event::EventType eventType) {
  if (eventType == Event::KeyPressEventType) {
    return true;
  }

  return false;
}

void KeyPressEvent::KeyPressEventHandler::HandleEvent(Event* event) {
  if (event != 0x0) {
    if (event->GetEventType() == Event::KeyPressEventType) {
      KeyPressEvent* ev = (KeyPressEvent*)event;
      printf("KeyPressed: %s\n", GetKeyName(ev->GetKey()));
      keys[ev->GetKey()] = true;
    }
  }
}

/*
void KeyPressEvent::KeyPressEventHandler::HandleEvent(Event event)
{
        if(event.GetEventType() == Event::KeyPressEventType)
        {
                KeyPressEvent ev = *((KeyPressEvent*)&event);
                printf("KeyPressed: %s\n", GetKeyName(ev.GetKey()));
                keys[ev.GetKey()] = true;
        }
}
*/

KeyPressEvent::KeyPressEventHandler::KeyPressEventHandler() {}

KeyPressEvent::KeyPressEventHandler::~KeyPressEventHandler() {}

}  // End namespace OpenArena
