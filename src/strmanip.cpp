#include "../include/strmanip.h"

bool Truth(std::string str)
{
	if (toupper(str[0]) == 'T' || str[0] == '1')
		return true;
	else
		return false;
}

int Integer(std::string str)
{
	int last = str.length() - 1;
	int number = 0;

	for (int x = last; x>=0; x--)
	{
		switch(str[x])
		{
		case '1':
			number += (int)pow(10, last-x);
			break;
		case '2':
			number += 2 * (int)pow(10, last-x);
			break;
		case '3':
			number += 3 * (int)pow(10, last-x);
			break;
		case '4':
			number += 4 * (int)pow(10, last-x);
			break;
		case '5':
			number += 5 * (int)pow(10, last-x);
			break;
		case '6':
			number += 6 * (int)pow(10, last-x);
			break;
		case '7':
			number += 7 * (int)pow(10, last-x);
			break;
		case '8':
			number += 8 * (int)pow(10, last-x);
			break;
		case '9':
			number += 9 * (int)pow(10, last-x);
		}
	}
	return number;
}

float Floating(std::string str)
{
	//this doesn't work right yet so use atof for now

	int last = str.length() - 1;
	float number = 0.0f;
	bool period = false;

	for (int x = last; x>=0; x--)
	{
		switch(str[x])
		{
		case '1':
			number += (float)pow(10, last-x);
			break;
		case '2':
			number += 2 * (float)pow(10, last-x);
			break;
		case '3':
			number += 3 * (float)pow(10, last-x);
			break;
		case '4':
			number += 4 * (float)pow(10, last-x);
			break;
		case '5':
			number += 5 * (float)pow(10, last-x);
			break;
		case '6':
			number += 6 * (float)pow(10, last-x);
			break;
		case '7':
			number += 7 * (float)pow(10, last-x);
			break;
		case '8':
			number += 8 * (float)pow(10, last-x);
			break;
		case '9':
			number += 9 * (float)pow(10, last-x);
			break;
		case '.':
			if (!period)
			{
				number *= (float)pow(10, -(last-x));
				last -= (x+1);
				period = true;
			}
			else
				return number;

		}
	}

	if(str[0] =='-')
		return -number;
	else
		return number;
}

string KeyString(uint8 key)
{
	switch (key)
	{
	case VK_LBUTTON:
		return "mouse1";
	case VK_RBUTTON:
		return "mouse2";
	case VK_MBUTTON:
		return "mouse3";
	case VK_TAB:
		return "tab";
	case VK_RETURN:
		return "enter";
	case VK_SHIFT:
		return "shift";
	case VK_CONTROL:
		return "control";
	case VK_PAUSE:
		return "pause";
	case VK_CAPITAL:
		return "capslock";
	case VK_ESCAPE:
		return "esc";
	case VK_SPACE:
		return "space";
	case VK_PRIOR:
		return "pageup";
	case VK_NEXT:
		return "pagedown";
	case VK_END:
		return "end";
	case VK_HOME:
		return "home";
	case VK_LEFT:
		return "left";
	case VK_UP:
		return "up";
	case VK_RIGHT:
		return "right";
	case VK_DOWN:
		return "down";
	case VK_INSERT:
		return "insert";
	case VK_DELETE:
		return "delete";
	case VK_LWIN:
		return "lwin";
	case VK_RWIN:
		return "rwin";
	case VK_APPS:
		return "apps";
	case VK_NUMPAD0:
		return "numpad0";
	case VK_NUMPAD1:
		return "numpad1";
	case VK_NUMPAD2:
		return "numpad2";
	case VK_NUMPAD3:
		return "numpad3";
	case VK_NUMPAD4:
		return "numpad4";
	case VK_NUMPAD5:
		return "numpad5";
	case VK_NUMPAD6:
		return "numpad6";
	case VK_NUMPAD7:
		return "numpad7";
	case VK_NUMPAD8:
		return "numpad8";
	case VK_NUMPAD9:
		return "numpad9";
	case VK_MULTIPLY:
		return "numpad*";
	case VK_ADD:
		return "numpad+";
	case VK_SUBTRACT:
		return "numpad-";
	case VK_DIVIDE:
		return "numpad/";
	case VK_F1:
		return "f1";
	case VK_F2:
		return "f2";
	case VK_F3:
		return "f3";
	case VK_F4:
		return "f4";
	case VK_F5:
		return "f5";
	case VK_F6:
		return "f6";
	case VK_F7:
		return "f7";
	case VK_F8:
		return "f8";
	case VK_F9:
		return "f9";
	case VK_F10:
		return "f10";
	case VK_F11:
		return "f11";
	case VK_F12:
		return "f2";
	case VK_NUMLOCK:
		return "numlock";
	case VK_SCROLL:
		return "scroll";
	case VK_SEPARATOR:
		return "separator";
	default:
		return "null";
	};
}
uint8 KeyName(std::string str)
{
	if (str.length() > 1)
	{
		if (str.substr(0,2) == "up")
			return VK_UP;
		else if (str.substr(0,4) == "down")
			return VK_DOWN;
		else if (str.substr(0,3) == "esc")
			return VK_ESCAPE;
		else if (str.substr(0,6) == "pageup")
			return VK_PRIOR;
		else if (str.substr(0,8) == "pagedown")
			return VK_NEXT;
		else if (str.substr(0,5) == "right")
			return VK_RIGHT;
		else if (str.substr(0,4) == "left")
			return VK_LEFT;
		else if (str.substr(0,5) == "space")
			return VK_SPACE;
		else if (str.substr(0,6) == "mouse1")
			return VK_LBUTTON;
		else if (str.substr(0,6) == "mouse2")
			return VK_RBUTTON;
		else if (str.substr(0,6) == "mouse3")
			return VK_MBUTTON;
		else if (str.substr(0,4) == "home")
			return VK_HOME;
		else if (str.substr(0,3) == "end")
			return VK_END;
		else if (str.substr(0,3) == "tab")
			return VK_TAB;
		else if (str.substr(0,5) == "enter")
			return VK_RETURN;
		else if (str.substr(0,6) == "insert")
			return VK_INSERT;
		else if (str.substr(0,6) == "delete")
			return VK_DELETE;
		else if (str.substr(0,7) == "control")
			return VK_CONTROL;
		else if (str.substr(0,5) == "shift")
			return VK_SHIFT;
		else if (str.substr(0,7) == "numpad0")
			return VK_NUMPAD0;
		else if (str.substr(0,7) == "numpad1")
			return VK_NUMPAD1;
		else if (str.substr(0,7) == "numpad2")
			return VK_NUMPAD2;
		else if (str.substr(0,7) == "numpad3")
			return VK_NUMPAD3;
		else if (str.substr(0,7) == "numpad4")
			return VK_NUMPAD4;
		else if (str.substr(0,7) == "numpad5")
			return VK_NUMPAD5;
		else if (str.substr(0,7) == "numpad6")
			return VK_NUMPAD6;
		else if (str.substr(0,7) == "numpad7")
			return VK_NUMPAD7;
		else if (str.substr(0,7) == "numpad8")
			return VK_NUMPAD8;
		else if (str.substr(0,7) == "numpad9")
			return VK_NUMPAD9;
		else if (str.substr(0,9) == "separator")
			return VK_SEPARATOR;
		else if (str.substr(0,4) == "lwin")
			return VK_LWIN;
		else if (str.substr(0,4) == "rwin")
			return VK_RWIN;
		else if (str.substr(0,4) == "apps")
			return VK_APPS;
		else if (str.substr(0,7) == "numpad*")
			return VK_MULTIPLY;
		else if (str.substr(0,7) == "numpad+")
			return VK_ADD;
		else if (str.substr(0,7) == "numpad/")
			return VK_DIVIDE;
		else if (str.substr(0,7) == "numpad-")
			return VK_SUBTRACT;
		else if (str.substr(0,6) == "scroll")
			return VK_SCROLL;
		else if (str.substr(0,7) == "numlock")
			return VK_NUMLOCK;
		else if (str.substr(0,5) == "pause")
			return VK_PAUSE;
		else if (str.substr(0,8) == "capslock")
			return VK_CAPITAL;
		


		/*uncomment this to enable f1 as a mappable key
		else if(str.substr(0,2) == "f1")
		return VK_F1;
		*/

		else if (str.substr(0,2) == "f2")
			return VK_F2;
		else if (str.substr(0,2) == "f3")
			return VK_F3;
		else if (str.substr(0,2) == "f4")
			return VK_F4;
		else if (str.substr(0,2) == "f5")
			return VK_F5;
		else if (str.substr(0,2) == "f6")
			return VK_F6;
		else if (str.substr(0,2) == "f7")
			return VK_F7;
		else if (str.substr(0,2) == "f8")
			return VK_F8;
		else if (str.substr(0,2) == "f9")
			return VK_F9;
		else if (str.substr(0,2) == "f10")
			return VK_F10;
		else if (str.substr(0,2) == "f11")
			return VK_F11;
		else if (str.substr(0,2) == "f12")
			return VK_F12;
		//Add Game specific keys here and e-mail headhunter45@hotmail.com subject OpenArena keys so I can add them please
		else if (str.substr(0,4) == "null")
			return NULL;
		else
			return NULL;
	}
	else
	{
		if(str[0] == '~' || str[0] == '`')
			return VK_OEM_3;
		else if (str[0] == '?' || str[0] == '/')
            return VK_OEM_2;
		else if (str[0] == '.' || str[0] == '>')
			return VK_OEM_PERIOD;
		else if (str[0] == '+' || str[0] == '=')
			return VK_OEM_PLUS;
		else if (str[0] == ';' || str[0] == ':')
			return VK_OEM_1;
		else if (str[0] == ',' || str[0] == '<')
			return VK_OEM_COMMA;
		else if (str[0] == '-' || str[0] == '_')
			return VK_OEM_MINUS;
		else if (str[0] == '[' || str[0] == '{')
			return VK_OEM_4;
		else if (str[0] == ']' || str[0] == '}')
			return VK_OEM_6;
		else if (str[0] == '\\' || str[0] == '|')
			return VK_OEM_5;
		else if (str[0] == '\'' || str[0] == '"')
			return VK_OEM_7;
		else
            return toupper(str[0]);
	}
}

string Right(string str, uint32 len)
{
	return str.substr(str.length()-len, len);
}

string Left(string str, uint32 len)
{
	return str.substr(0, len);
}

string tolower(string str)
{
	for(uint32 i=0; i<str.length(); i++)
		str[i] = tolower(str[i]);

	return str;
}

string toupper(string str)
{
	for(uint32 i=0; i<str.length(); i++)
		str[i] = toupper(str[i]);

	return str;
}

string word(string str, uint32 wordNum)
{
	///////////////
	//stopped here
	///////////////
	uint32 start = 0;
	uint32 length = 0;
	uint32 maxLength = str.length();
	if(str.length() > 0)
	{
		if(wordNum < 1)
		{
			while (!isspace(str[++length]) && length < maxLength);

			return str.substr(start, length);
		}
		else
		{
			while(isspace(str[start]))
				++start;

			for(uint32 i=0; i<wordNum; i++)
			{
				while(start <maxLength && !isspace(str[start]))// && start <= maxLength)
					++start;
				while(start < maxLength && isspace(str[start]))
					++start;
			}

;

			while((start+length) < maxLength && !isspace(str[start+length]))
				++length;

			return str.substr(start, length);
		}
	}
	else
	{
		return "";
	}
}