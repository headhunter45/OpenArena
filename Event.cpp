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
#include "Event.h"

// clang-format on

namespace OpenArena {
Event::Event() {
  SetEventType(UnknownEventType);
}

Event::~Event() {}

OpenArena::Event::EventType Event::GetEventType() {
  return _type;
}

void Event::SetEventType(OpenArena::Event::EventType type) {
  _type = type;
}

Event::EventHandler::EventHandler() {}

Event::EventHandler::~EventHandler() {}

bool Event::EventHandler::Handles(Event::EventType eventType) {
  return false;
}

void Event::EventHandler::HandleEvent(Event* event) {}

/*
void Event::EventHandler::HandleEvent(Event event)
{
}
*/
}  // End namespace OpenArena
