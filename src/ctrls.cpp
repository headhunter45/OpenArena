////////////////////////////////////////////////////////////////////////////////
//
//	Module:		ctrls.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	10-20-2003
//	Editors:	Tom Hicks
//
//	Purpose:
//		To implement a system for managing a bindable control scheme.
//
//	Summary of Methods:
//	ControlSchemeClass
//		void LoadDefaultControlScheme();
//			-Loads the default control scheme
//		void ClearControlScheme();
//			-Clears the control scheme
//		void Unbind(uint8 key);
//			-Removes key from all control lists.
//
//	Summary of Properties:
//	ControlSchemeClass
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

#include "../include/ctrls.h"

void ControlSchemeClass::LoadDefaultControlScheme()
{
	forward.Insert(VK_LBUTTON);
	backward.Insert(VK_RBUTTON);
	lookLeft.Insert(VK_LEFT);
	lookRight.Insert(VK_RIGHT);
	lookUp.Insert(VK_UP);
	lookDown.Insert(VK_DOWN);
	moveLeft.Insert('S');
	moveRight.Insert('D');
	moveUp.Insert(VK_SPACE);
	moveDown.Insert('A');
	firePrimary.Insert('F');
	fireSecondary.Insert('G');
	weaponNext.Insert('T');
	weaponPrev.Insert('R');
	toggleLights.Insert('L');
	toggleFPS.Insert('P');
	toggleConsole.Insert('~');
	toggleMouseLook.Insert('M');
	quickMouseLook.Insert('Q');
	rollLeft.Insert('W');
	rollRight.Insert('E');
}
void ControlSchemeClass::ClearControlScheme()
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

void ControlSchemeClass::Unbind(uint8 key)
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

bool ControlSchemeClass::Bind(uint32 action, uint8 key)
{
	switch(action)
	{
	case CTRLS_FORWARD:
		{
			Unbind(key);
			forward.Insert(key);
			return true;
		}
	case CTRLS_BACKWARD:
		{
            Unbind(key);
			backward.Insert(key);
			return true;
		}
	case CTRLS_LOOKLEFT:
		{
			Unbind(key);
			lookLeft.Insert(key);
			return true;
		}
	case CTRLS_LOOKRIGHT:
		{
			Unbind(key);
			lookRight.Insert(key);
			return true;
		}
	case CTRLS_LOOKUP:
		{
			Unbind(key);
			lookUp.Insert(key);
			return true;
		}
	case CTRLS_LOOKDOWN:
		{
			Unbind(key);
			lookDown.Insert(key);
			return true;
		}
	case CTRLS_MOVELEFT:
		{
			Unbind(key);
			moveLeft.Insert(key);
			return true;
		}
	case CTRLS_MOVERIGHT:
		{
			Unbind(key);
			moveRight.Insert(key);
			return true;
		}
	case CTRLS_MOVEUP:
		{
			Unbind(key);
			moveUp.Insert(key);
			return true;
		}
	case CTRLS_MOVEDOWN:
		{
			Unbind(key);
			moveDown.Insert(key);
			return true;
		}
	case CTRLS_ROLLLEFT:
		{
			Unbind(key);
			rollLeft.Insert(key);
			return true;
		}
	case CTRLS_ROLLRIGHT:
		{
			Unbind(key);
			rollRight.Insert(key);
			return true;
		}
	case CTRLS_FIREPRIMARY:
		{
			Unbind(key);
			firePrimary.Insert(key);
			return true;
		}
	case CTRLS_FIRESECONDARY:
		{
			Unbind(key);
			fireSecondary.Insert(key);
			return true;
		}
	case CTRLS_WEAPONNEXT:
		{
			Unbind(key);
			weaponNext.Insert(key);
			return true;
		}
	case CTRLS_WEAPONPREV:
		{
			Unbind(key);
			weaponPrev.Insert(key);
			return true;
		}
	case CTRLS_TOGGLE_LIGHTS:
		{
			Unbind(key);
			toggleLights.Insert(key);
			return true;
		}
	case CTRLS_TOGGLE_FPS:
		{
			Unbind(key);
			toggleFPS.Insert(key);
			return true;
		}
	case CTRLS_TOGGLE_CONSOLE:
		{
			Unbind(key);
			toggleConsole.Insert(key);
			return true;
		}
	case CTRLS_TOGGLE_MOUSELOOK:
		{
			Unbind(key);
			toggleMouseLook.Insert(key);
			return true;
		}
	case CTRLS_QUICKMOUSELOOK:
		{
			Unbind(key);
			quickMouseLook.Insert(key);
			return true;
		}
	default:
		return false;
	}
}