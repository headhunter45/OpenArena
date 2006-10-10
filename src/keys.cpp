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
