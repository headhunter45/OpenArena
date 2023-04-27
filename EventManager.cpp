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
#include "EventManager.h"

#include <cstdlib>
#include <iostream>

namespace OpenArena {
EventManager::EventManager() {}

void EventManager::SendEvent(Event* event) {
  unsigned int index;

  for (index = 0; index < eventHandlers.Length(); index++) {
    Event::EventHandler* handler = eventHandlers[index];
    if (handler->Handles(event->GetEventType())) {
      handler->HandleEvent(event);
    }
  }

  delete event;
}

/*
void EventManager::SendEvent(Event event)
{
        unsigned int index;

        for(index=0; index < eventHandlers.Length(); index++)
        {
                Event::EventHandler* handler = eventHandlers[index];
                if(handler->Handles(event.GetEventType()))
                {
                        handler->HandleEvent(event);
                }
        }
}
*/

void EventManager::RegisterEventHandler(Event::EventHandler* eventHandler) {
  eventHandlers.Insert(eventHandler);
}
};  // namespace OpenArena
