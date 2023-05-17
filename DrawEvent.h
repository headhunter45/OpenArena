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

#ifndef OpenArena__DrawEvent_h__
#define OpenArena__DrawEvent_h__
// clang-format off
#include "config.h"
#include "Event.h"
#include "level.h"

// clang-format on

namespace OpenArena {
class DrawEvent : public OpenArena::Event {
 public:
  class DrawEventHandler : public EventHandler {
   public:
    DrawEventHandler(Level* level);
    virtual bool Handles(EventType type);
    virtual void HandleEvent(Event* event);
    // virtual void HandleEvent(Event event);
   private:
    Level* _level;
  };

  DrawEvent();
  virtual ~DrawEvent();
};
};  // End namespace OpenArena

#endif  // End !defined(OpenArena__DrawEvent_h__)
