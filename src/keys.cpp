#include "../include/keys.h"

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
