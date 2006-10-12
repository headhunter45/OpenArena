/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks   *
 *   tomhicks@cse.buffalo.edu   *
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
#ifndef __OpenArena_EventMangaer_h__
#define __OpenArena_EventMangaer_h__

#include "Events/Event.h"
#include "list.h"

/**
 * @file EventManager.h
 * @breif Specification of the EventManager class 
 * This file along with EventManager.cpp implement the EventManager
 * class.  The EventManager class collects and redistributes events
 * in a fashion similar to AWT's EventListeners.
 * 
 * @see EventManager.cpp
 */
 
namespace OpenArena
{
	class EventManager
	{
	public:
		EventManager();
		void SendEvent(Event* event);
		void RegisterEventHandler(Event::EventHandler* eventHandler);
	private:
		list<Event::EventHandler*> eventHandlers;
	};
}
#endif /*__OpenArena_EventMangaer_h__*/
