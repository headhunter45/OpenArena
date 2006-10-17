/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks                                       *
 *   tomhicks@cse.buffalo.edu                                              *
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
/**
 * @file EventManager.cpp
 * @breif Implementation of the EventManager class 
 * This file along with EventManager.h implement the EventManager
 * class.  The EventManager class collects and redistributes events
 * in a fashion similar to AWT's EventListeners.
 * 
 * @see EventManager.h
 */
#include "EventManager.h"
#include <cstdlib>
#include <iostream>

namespace OpenArena
{
	EventManager::EventManager()
	{
	}
	

	void EventManager::SendEvent(Events::Event* event)
	{
		unsigned int index;
		
		for(index=0; index < eventHandlers.Length(); index++)
		{
			Events::Event::EventHandler* handler = eventHandlers[index];
			if(handler->Handles(event->GetEventType()))
			{
				handler->HandleEvent(event);
			}
		}
		
		delete event;
	}
	
	/*
	void EventManager::SendEvent(Events::Event event)
	{
		unsigned int index;
		
		for(index=0; index < eventHandlers.Length(); index++)
		{
			Events::Event::EventHandler* handler = eventHandlers[index];
			if(handler->Handles(event.GetEventType()))
			{
				handler->HandleEvent(event);
			}
		}
	}
	*/
	
	void EventManager::RegisterEventHandler(Events::Event::EventHandler* eventHandler)
	{
		eventHandlers.Insert(eventHandler);
	}
};
