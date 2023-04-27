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
#ifndef OpenArena__KeyReleaseEvent_h__
#define OpenArena__KeyReleaseEvent_h__
#include "Event.h"
#include "keys.h"

namespace OpenArena {
class KeyReleaseEvent : public Event {
 public:
  KeyReleaseEvent(OpenArena::Keys key);
  ~KeyReleaseEvent();
  virtual OpenArena::Keys GetKey();

  class KeyReleaseEventHandler : public Event::EventHandler {
   public:
    KeyReleaseEventHandler();
    virtual bool Handles(Event::EventType eventType);
    virtual void HandleEvent(Event* event);
    // virtual void HandleEvent(Event event);
    virtual ~KeyReleaseEventHandler();
  };

 private:
  OpenArena::Keys _key;
};
};  // End namespace OpenArena

#endif  // OpenArena__KeyReleaseEvent_h__
