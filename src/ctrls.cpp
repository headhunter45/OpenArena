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
////////////////////////////////////////////////////////////////////////////////
//
//	Module:		ctrls.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	06-19-2005
//	Editors:	Tom Hicks
//
//	Purpose:
//		To implement a system for managing a bindable control scheme.
//
//	Summary of Methods:
//	ControlScheme
//		void LoadDefaultControlScheme();
//			-Loads the default control scheme
//		void ClearControlScheme();
//			-Clears the control scheme
//		void Unbind(uint8 key);
//			-Removes key from all control lists.
//
//	Summary of Properties:
//	ControlScheme
//		-list<uint8> forward;
//			A list of the VKeys associated with forward.
//		-list<uint8> backward;
//			A list of the VKeys associated with backward.
//		-list<uint8> lookLeft;
//			A list of the VKeys associated with turning left.
//		-list<uint8> lookRight;
//			A list of the VKeys associated with turning right.
//		-list<uint8> lookUp;
//			A list of the VKeys associated with looking up.
//		-list<uint8> lookDown;
//			A list of the VKeys associated with looking down.
//		-list<uint8> moveLeft;
//			A list of the VKeys associated with strafing left.
//		-list<uint8> moveRight;
//			A list of the VKeys associated with strafing right.
//		-list<uint8> moveUp;
//			A list of the VKeys associated with jumping.
//		-list<uint8> moveDown;
//			A list of the VKeys associated with crouching.
//		-list<uint8> firePrimary;
//			A list of the VKeys associated with activating the primary ability of the active item.
//		-list<uint8> fireSecondary;
//			A list of the VKeys associated with activating the secondary ablilty of the active item.
//		-list<uint8> weaponNext;
//			A list of the VKeys associated with switching to the next item.
//		-list<uint8> weaponPrev;
//			A list of the VKeys associated with switching to the previous item.
//		-list<uint8> toggleLights;
//			A list of the VKeys associated with turning lighting on and off.
//		-list<uint8> toggleFPS;
//			A list of the VKeys associated with turning the FPS display on and off.
//		-list<uint8> toggleConsole;
//			A list of the VKeys associated with toggling the display of the console.
//		-list<uint8> toggleMouseLook;
//			A list of the VKeys associated with toggling mouse look.
//		-list<uint8> quickMouseLook;
//			A list of the VKeys associated with temporarily switching the mouse look mode.
//		-list<uint8> rollLeft;
//			A list of the VKeys associated with rolling left.
//		-list<uint8> rollRight;	
//			A list of the VKeys associated with rolling right.
//
////////////////////////////////////////////////////////////////////////////////

#include "ctrls.h"

namespace OpenArena{
	void ControlScheme::LoadDefaultControlScheme()
	{
		forward.Insert(OpenArena::KEY_LBUTTON);
		backward.Insert(OpenArena::KEY_RBUTTON);
		lookLeft.Insert(OpenArena::KEY_LEFT);
		lookRight.Insert(OpenArena::KEY_RIGHT);
		lookUp.Insert(OpenArena::KEY_UP);
		lookDown.Insert(OpenArena::KEY_DOWN);
		moveLeft.Insert(OpenArena::KEY_S);
		moveRight.Insert(OpenArena::KEY_D);
		moveUp.Insert(OpenArena::KEY_SPACE);
		moveDown.Insert(OpenArena::KEY_A);
		firePrimary.Insert(OpenArena::KEY_F);
		fireSecondary.Insert(OpenArena::KEY_G);
		weaponNext.Insert(OpenArena::KEY_T);
		weaponPrev.Insert(OpenArena::KEY_R);
		toggleLights.Insert(OpenArena::KEY_L);
		toggleFPS.Insert(OpenArena::KEY_P);
		toggleConsole.Insert(OpenArena::KEY_OEM_3);
		toggleMouseLook.Insert(OpenArena::KEY_M);
		quickMouseLook.Insert(OpenArena::KEY_Q);
		rollLeft.Insert(OpenArena::KEY_W);
		rollRight.Insert(OpenArena::KEY_E);
	}
	void ControlScheme::ClearControlScheme()
	{
		backward.Clear();
		firePrimary.Clear();
		fireSecondary.Clear();
		forward.Clear();
		lookDown.Clear();
		lookUp.Clear();
		lookRight.Clear();
		lookLeft.Clear();
		moveDown.Clear();
		moveUp.Clear();
		moveLeft.Clear();
		moveRight.Clear();
		quickMouseLook.Clear();
		toggleConsole.Clear();
		toggleFPS.Clear();
		toggleLights.Clear();
		toggleMouseLook.Clear();
		weaponNext.Clear();
		weaponPrev.Clear();
	}

	void ControlScheme::Unbind(uint8 key)
	{
		backward.Remove(key);
		firePrimary.Remove(key);
		fireSecondary.Remove(key);
		forward.Remove(key);
		lookDown.Remove(key);
		lookUp.Remove(key);
		lookRight.Remove(key);
		lookLeft.Remove(key);
		moveDown.Remove(key);
		moveUp.Remove(key);
		moveRight.Remove(key);
		quickMouseLook.Remove(key);
		toggleConsole.Remove(key);
		toggleFPS.Remove(key);
		toggleLights.Remove(key);
		toggleMouseLook.Remove(key);
		weaponNext.Remove(key);
		weaponPrev.Remove(key);
	}

	bool ControlScheme::Bind(uint32 action, uint8 key)
	{
		switch(action)
		{
		case ACTION_FORWARD:
			{
				Unbind(key);
				forward.Insert(key);
				return true;
			}
		case ACTION_BACKWARD:
			{
				Unbind(key);
				backward.Insert(key);
				return true;
			}
		case ACTION_LOOKLEFT:
			{
				Unbind(key);
				lookLeft.Insert(key);
				return true;
			}
		case ACTION_LOOKRIGHT:
			{
				Unbind(key);
				lookRight.Insert(key);
				return true;
			}
		case ACTION_LOOKUP:
			{
				Unbind(key);
				lookUp.Insert(key);
				return true;
			}
		case ACTION_LOOKDOWN:
			{
				Unbind(key);
				lookDown.Insert(key);
				return true;
			}
		case ACTION_MOVELEFT:
			{
				Unbind(key);
				moveLeft.Insert(key);
				return true;
			}
		case ACTION_MOVERIGHT:
			{
				Unbind(key);
				moveRight.Insert(key);
				return true;
			}
		case ACTION_MOVEUP:
			{
				Unbind(key);
				moveUp.Insert(key);
				return true;
			}
		case ACTION_MOVEDOWN:
			{
				Unbind(key);
				moveDown.Insert(key);
				return true;
			}
		case ACTION_ROLLLEFT:
			{
				Unbind(key);
				rollLeft.Insert(key);
				return true;
			}
		case ACTION_ROLLRIGHT:
			{
				Unbind(key);
				rollRight.Insert(key);
				return true;
			}
		case ACTION_FIREPRIMARY:
			{
				Unbind(key);
				firePrimary.Insert(key);
				return true;
			}
		case ACTION_FIRESECONDARY:
			{
				Unbind(key);
				fireSecondary.Insert(key);
				return true;
			}
		case ACTION_WEAPONNEXT:
			{
				Unbind(key);
				weaponNext.Insert(key);
				return true;
			}
		case ACTION_WEAPONPREV:
			{
				Unbind(key);
				weaponPrev.Insert(key);
				return true;
			}
		case ACTION_TOGGLE_LIGHTS:
			{
				Unbind(key);
				toggleLights.Insert(key);
				return true;
			}
		case ACTION_TOGGLE_FPS:
			{
				Unbind(key);
				toggleFPS.Insert(key);
				return true;
			}
		case ACTION_TOGGLE_CONSOLE:
			{
				Unbind(key);
				toggleConsole.Insert(key);
				return true;
			}
		case ACTION_TOGGLE_MOUSELOOK:
			{
				Unbind(key);
				toggleMouseLook.Insert(key);
				return true;
			}
		case ACTION_QUICKMOUSELOOK:
			{
				Unbind(key);
				quickMouseLook.Insert(key);
				return true;
			}
		default:
			return false;
		}
	}
};
