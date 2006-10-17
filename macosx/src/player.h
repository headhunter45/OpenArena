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
#ifndef __PLAYER_H__
#define __PLAYER_H__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "EventManager.h"
#include "camera.h"
#include "ctrls.h"

namespace OpenArena
{
	class Player
	{
	public:
		void Load();
		void Save();
		void CreateCharacter();
		void AddItem(unsigned int item);
		void RemoveItem(unsigned int item);
		
		ControlScheme controls;
		Camera camera;
		EventManager* eventManager;
	
		class EventHandler
		{
		public:
			
		private:
		
		};
		
	private:
	};
};
#endif
