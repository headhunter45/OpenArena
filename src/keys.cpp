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
#include "keys.h"

#include <string>

using std::string;

char OpenArena::KeyToASCII(Keys key, bool shift)
{
	if(key == KEY_UNKNOWN)
	{
		return '\0';
	}
	else
	{
		switch(key)
		{
		case KEY_OEM_1:
			if(shift)
			{
				return ':';
			}
			else
			{
				return ';';
			}
		case KEY_OEM_2:
			if(shift)
			{
				return '?';
			}
			else
			{
				return '/';
			}
		case KEY_OEM_3:
			if(shift)
			{
				return '~';
			}
			else
			{
				return '`';
			}
		case KEY_OEM_4:
			if(shift)
			{
				return '{';
			}
			else
			{
				return '[';
			}
		case KEY_OEM_5:
			if(shift)
			{
				return '|';
			}
			else
			{
				return '\\';
			}
		case KEY_OEM_6:
			if(shift)
			{
				return '}';
			}
			else
			{
				return ']';
			}
		case KEY_OEM_7:
			if(shift)
			{
				return '\'';
			}
			else
			{
				return '"';
			}
		case KEY_OEM_PERIOD:
			if(shift)
			{
				return '>';
			}
			else
			{
				return '.';
			}
		case KEY_OEM_PLUS:
			if(shift)
			{
				return '+';
			}
			else
			{
				return '=';
			}
		case KEY_OEM_COMMA:
			if(shift)
			{
				return '<';
			}
			else
			{
				return ',';
			}
		case KEY_OEM_MINUS:
			if(shift)
			{
				return '_';
			}
			else
			{
				return '-';
			}
		default:
			if(key >= KEY_A && key <= KEY_Z)
			{
				if(shift)
				{
					return key - KEY_A + 'A';
				}
				else
				{
					return key - KEY_A + 'a';
				}
			}
			else if(key >= KEY_0 && key <= KEY_9)
			{
				if(shift)
				{
					switch(key - KEY_0)
					{
					case 0:
						return ')';
					case 1:
						return '!';
					case 2:
						return '@';
					case 3:
						return '#';
					case 4:
						return '$';
					case 5:
						return '%';
					case 6:
						return '^';
					case 7:
						return '&';
					case 8:
						return '*';
					case 9:
						return '(';	
					}
				}
				else
				{
					return key - KEY_0 + '0';
				}
			}
			else
			{
				return '\0';
			}
		}
	}
	return '\0';
}

const char* OpenArena::GetKeyName(Keys key)
{
	switch(key)
	{
	case KEY_UNKNOWN:
		return "unknown";
	case KEY_BUTTON0:
		return "button0";
	case KEY_BUTTON1:
		return "button1";
	case KEY_BUTTON2:
		return "button2";
	case KEY_BUTTON3:
		return "button3";
	case KEY_BUTTON4:
		return "button4";
	case KEY_LEFT:
		return "left";
	case KEY_RIGHT:
		return "right";
	case KEY_UP:
		return "up";
	case KEY_DOWN:
		return "down";
	case KEY_SPACE:
		return "space";
	case KEY_RETURN:
		return "return";
	case KEY_SHIFT:
		return "shift";
	case KEY_PAUSE:
		return "pause";
	case KEY_CONTROL:
		return "ctrl";
	case KEY_CAPITAL:
		return "caps";
	case KEY_ESCAPE:
		return "esc";
	case KEY_PRIOR:
		return "pgup";
	case KEY_NEXT:
		return "pgdn";
	case KEY_END:
		return "end";
	case KEY_HOME:
		return "home";
	case KEY_INSERT:
		return "insert";
	case KEY_DELETE:
		return "del";
	case KEY_LWIN:
		return "leftwin";
	case KEY_RWIN:
		return "rightwin";
	case KEY_APPS:
		return "apps";
	case KEY_NUMPAD0:
		return "kp0";
	case KEY_NUMPAD1:
	return "kp1";
	case KEY_NUMPAD2:
	return "kp2";
	case KEY_NUMPAD3:
		return "kp3";
	case KEY_NUMPAD4:
		return "kp4";
	case KEY_NUMPAD5:
		return "kp5";
	case KEY_NUMPAD6:
		return "kp6";
	case KEY_NUMPAD7:
		return "kp7";
	case KEY_NUMPAD8:
		return "kp8";
	case KEY_NUMPAD9:
		return "kp9";
	case KEY_MULTIPLY:
		return "multiply";
	case KEY_ADD:
		return "plus";
	case KEY_SUBTRACT:
		return "minus";
	case KEY_DIVIDE:
		return "divide";
	case KEY_F1:
		return "f1";
	case KEY_F2:
		return "f2";
	case KEY_F3:
		return "f3";
	case KEY_F4:
		return "f4";
	case KEY_F5:
		return "f5";
	case KEY_F6:
		return "f6";
	case KEY_F7:
		return "f7";
	case KEY_F8:
		return "f8";
	case KEY_F9:
		return "f9";
	case KEY_F10:
		return "f10";
	case KEY_F11:
		return "f11";
	case KEY_F12:
		return "f12";
	case KEY_NUMLOCK:
		return "numlock";
	case KEY_SCROLL:
		return "scrolllock";
	case KEY_SEPARATOR:
		return "_separator";
	case KEY_OEM_1:
		return "semicolon";
	case KEY_OEM_2:
		return "slash";
	case KEY_OEM_3:
		return "tilde";
	case KEY_OEM_4:
		return "leftbracket";
	case KEY_OEM_5:
		return "backslash";
	case KEY_OEM_6:
		return "rightbracket";
	case KEY_OEM_7:
		return "quote";
	case KEY_OEM_PERIOD:
		return "period";
	case KEY_OEM_PLUS:
		return "equals";
	case KEY_OEM_MINUS:
		return "minus";
	case KEY_OEM_COMMA:
		return "comma";
	case KEY_BACK:
		return "backspace";
	case KEY_TAB:
		return "tab";
	case KEY_0:
		return "0";
	case KEY_1:
		return "1";
	case KEY_2:
		return "2";
	case KEY_3:
		return "3";
	case KEY_4:
		return "4";
	case KEY_5:
		return "5";
	case KEY_6:
		return "6";
	case KEY_7:
		return "7";
	case KEY_8:
		return "8";
	case KEY_9:
		return "9";
	case KEY_A:
		return "a";
	case KEY_B:
		return "b";
	case KEY_C:
		return "c";
	case KEY_D:
		return "d";
	case KEY_E:
		return "e";
	case KEY_F:
		return "f";
	case KEY_G:
		return "g";
	case KEY_H:
		return "h";
	case KEY_I:
		return "i";
	case KEY_J:
		return "j";
	case KEY_K:
		return "k";
	case KEY_L:
		return "l";
	case KEY_M:
		return "m";
	case KEY_N:
		return "n";
	case KEY_O:
		return "o";
	case KEY_P:
		return "p";
	case KEY_Q:
		return "q";
	case KEY_R:
		return "r";
	case KEY_S:
		return "s";
	case KEY_T:
		return "t";
	case KEY_U:
		return "u";
	case KEY_V:
		return "v";
	case KEY_W:
		return "w";
	case KEY_X:
		return "x";
	case KEY_Y:
		return "y";
	case KEY_Z:
		return "z";
	case KEY_ALT_L:
		return "leftalt";
	case KEY_ALT_R:
		return "rightalt";
	case KEY_COMMAND:
		return "command";
	case KEY_ENTER:
		return "enter";
	case KEY_OPTION:
		return "option";	
	}
	
	return "invalid";
}

OpenArena::Keys OpenArena::GetKey(const char* keyName)
{
	string str = keyName;
	if (str.length() > 1)
	{
		if (str.substr(0,2) == "up")
			return OpenArena::KEY_UP;
		else if (str.substr(0,4) == "down")
			return OpenArena::KEY_DOWN;
		else if (str.substr(0,3) == "esc")
			return OpenArena::KEY_ESCAPE;
		else if (str.substr(0,6) == "pageup")
			return OpenArena::KEY_PRIOR;
		else if (str.substr(0,8) == "pagedown")
			return OpenArena::KEY_NEXT;
		else if (str.substr(0,5) == "right")
			return OpenArena::KEY_RIGHT;
		else if (str.substr(0,4) == "left")
			return OpenArena::KEY_LEFT;
		else if (str.substr(0,5) == "space")
			return OpenArena::KEY_SPACE;
		else if (str.substr(0,6) == "mouse1")
			return OpenArena::KEY_LBUTTON;
		else if (str.substr(0,6) == "mouse2")
			return OpenArena::KEY_RBUTTON;
		else if (str.substr(0,6) == "mouse3")
			return OpenArena::KEY_MBUTTON;
		else if (str.substr(0,4) == "home")
			return OpenArena::KEY_HOME;
		else if (str.substr(0,3) == "end")
			return OpenArena::KEY_END;
		else if (str.substr(0,3) == "tab")
			return OpenArena::KEY_TAB;
		else if (str.substr(0,5) == "enter")
			return OpenArena::KEY_RETURN;
		else if (str.substr(0,6) == "insert")
			return OpenArena::KEY_INSERT;
		else if (str.substr(0,6) == "delete")
			return OpenArena::KEY_DELETE;
		else if (str.substr(0,7) == "control")
			return OpenArena::KEY_CONTROL;
		else if (str.substr(0,5) == "shift")
			return OpenArena::KEY_SHIFT;
		else if (str.substr(0,7) == "numpad0")
			return OpenArena::KEY_NUMPAD0;
		else if (str.substr(0,7) == "numpad1")
			return OpenArena::KEY_NUMPAD1;
		else if (str.substr(0,7) == "numpad2")
			return OpenArena::KEY_NUMPAD2;
		else if (str.substr(0,7) == "numpad3")
			return OpenArena::KEY_NUMPAD3;
		else if (str.substr(0,7) == "numpad4")
			return OpenArena::KEY_NUMPAD4;
		else if (str.substr(0,7) == "numpad5")
			return OpenArena::KEY_NUMPAD5;
		else if (str.substr(0,7) == "numpad6")
			return OpenArena::KEY_NUMPAD6;
		else if (str.substr(0,7) == "numpad7")
			return OpenArena::KEY_NUMPAD7;
		else if (str.substr(0,7) == "numpad8")
			return OpenArena::KEY_NUMPAD8;
		else if (str.substr(0,7) == "numpad9")
			return OpenArena::KEY_NUMPAD9;
		else if (str.substr(0,9) == "separator")
			return OpenArena::KEY_SEPARATOR;
		else if (str.substr(0,4) == "lwin")
			return OpenArena::KEY_LWIN;
		else if (str.substr(0,4) == "rwin")
			return OpenArena::KEY_RWIN;
		else if (str.substr(0,4) == "apps")
			return OpenArena::KEY_APPS;
		else if (str.substr(0,7) == "numpad*")
			return OpenArena::KEY_MULTIPLY;
		else if (str.substr(0,7) == "numpad+")
			return OpenArena::KEY_ADD;
		else if (str.substr(0,7) == "numpad/")
			return OpenArena::KEY_DIVIDE;
		else if (str.substr(0,7) == "numpad-")
			return OpenArena::KEY_SUBTRACT;
		else if (str.substr(0,6) == "scroll")
			return OpenArena::KEY_SCROLL;
		else if (str.substr(0,7) == "numlock")
			return OpenArena::KEY_NUMLOCK;
		else if (str.substr(0,5) == "pause")
			return OpenArena::KEY_PAUSE;
		else if (str.substr(0,8) == "capslock")
			return OpenArena::KEY_CAPITAL;
		


		/*uncomment this to enable f1 as a mappable key
		else if(str.substr(0,2) == "f1")
			return OpenArena::KEY_F1;
		*/

		else if (str.substr(0,2) == "f2")
			return OpenArena::KEY_F2;
		else if (str.substr(0,2) == "f3")
			return OpenArena::KEY_F3;
		else if (str.substr(0,2) == "f4")
			return OpenArena::KEY_F4;
		else if (str.substr(0,2) == "f5")
			return OpenArena::KEY_F5;
		else if (str.substr(0,2) == "f6")
			return OpenArena::KEY_F6;
		else if (str.substr(0,2) == "f7")
			return OpenArena::KEY_F7;
		else if (str.substr(0,2) == "f8")
			return OpenArena::KEY_F8;
		else if (str.substr(0,2) == "f9")
			return OpenArena::KEY_F9;
		else if (str.substr(0,2) == "f10")
			return OpenArena::KEY_F10;
		else if (str.substr(0,2) == "f11")
			return OpenArena::KEY_F11;
		else if (str.substr(0,2) == "f12")
			return OpenArena::KEY_F12;
		//Add Game specific keys here and e-mail headhunter45@hotmail.com subject OpenArena keys so I can add them please
		else if (str.substr(0,4) == "null")
			return OpenArena::KEY_UNKNOWN;
		else
			return OpenArena::KEY_UNKNOWN;
	}
	else
	{
		if(str[0] == '~' || str[0] == '`')
			return OpenArena::KEY_OEM_3;
		else if (str[0] == '?' || str[0] == '/')
            return OpenArena::KEY_OEM_2;
		else if (str[0] == '.' || str[0] == '>')
			return OpenArena::KEY_OEM_PERIOD;
		else if (str[0] == '+' || str[0] == '=')
			return OpenArena::KEY_OEM_PLUS;
		else if (str[0] == ';' || str[0] == ':')
			return OpenArena::KEY_OEM_1;
		else if (str[0] == ',' || str[0] == '<')
			return OpenArena::KEY_OEM_COMMA;
		else if (str[0] == '-' || str[0] == '_')
			return OpenArena::KEY_OEM_MINUS;
		else if (str[0] == '[' || str[0] == '{')
			return OpenArena::KEY_OEM_4;
		else if (str[0] == ']' || str[0] == '}')
			return OpenArena::KEY_OEM_6;
		else if (str[0] == '\\' || str[0] == '|')
			return OpenArena::KEY_OEM_5;
		else if (str[0] == '\'' || str[0] == '"')
			return OpenArena::KEY_OEM_7;
		else if (isalpha(str[0]))
			return (OpenArena::Keys)(toupper(str[0]) - 'A' + OpenArena::KEY_A); 
		else if(isdigit(str[0]))
			return (OpenArena::Keys)(str[0] - '0' + OpenArena::KEY_0);
		else
			return OpenArena::KEY_UNKNOWN;
	}
}


