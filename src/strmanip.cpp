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
			number += (int)pow(10.0, last-x);
			break;
		case '2':
			number += 2 * (int)pow(10.0, last-x);
			break;
		case '3':
			number += 3 * (int)pow(10.0, last-x);
			break;
		case '4':
			number += 4 * (int)pow(10.0, last-x);
			break;
		case '5':
			number += 5 * (int)pow(10.0, last-x);
			break;
		case '6':
			number += 6 * (int)pow(10.0, last-x);
			break;
		case '7':
			number += 7 * (int)pow(10.0, last-x);
			break;
		case '8':
			number += 8 * (int)pow(10.0, last-x);
			break;
		case '9':
			number += 9 * (int)pow(10.0, last-x);
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
			number += (float)pow(10.0, last-x);
			break;
		case '2':
			number += 2 * (float)pow(10.0, last-x);
			break;
		case '3':
			number += 3 * (float)pow(10.0, last-x);
			break;
		case '4':
			number += 4 * (float)pow(10.0, last-x);
			break;
		case '5':
			number += 5 * (float)pow(10.0, last-x);
			break;
		case '6':
			number += 6 * (float)pow(10.0, last-x);
			break;
		case '7':
			number += 7 * (float)pow(10.0, last-x);
			break;
		case '8':
			number += 8 * (float)pow(10.0, last-x);
			break;
		case '9':
			number += 9 * (float)pow(10.0, last-x);
			break;
		case '.':
			if (!period)
			{
				number *= (float)pow(10.0, -(last-x));
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
	case KEY_LBUTTON:
		return "mouse1";
	case KEY_RBUTTON:
		return "mouse2";
	case KEY_MBUTTON:
		return "mouse3";
	case KEY_TAB:
		return "tab";
	case KEY_RETURN:
		return "enter";
	case KEY_SHIFT:
		return "shift";
	case KEY_CONTROL:
		return "control";
	case KEY_PAUSE:
		return "pause";
	case KEY_CAPITAL:
		return "capslock";
	case KEY_ESCAPE:
		return "esc";
	case KEY_SPACE:
		return "space";
	case KEY_PRIOR:
		return "pageup";
	case KEY_NEXT:
		return "pagedown";
	case KEY_END:
		return "end";
	case KEY_HOME:
		return "home";
	case KEY_LEFT:
		return "left";
	case KEY_UP:
		return "up";
	case KEY_RIGHT:
		return "right";
	case KEY_DOWN:
		return "down";
	case KEY_INSERT:
		return "insert";
	case KEY_DELETE:
		return "delete";
	case KEY_LWIN:
		return "lwin";
	case KEY_RWIN:
		return "rwin";
	case KEY_APPS:
		return "apps";
	case KEY_NUMPAD0:
		return "numpad0";
	case KEY_NUMPAD1:
		return "numpad1";
	case KEY_NUMPAD2:
		return "numpad2";
	case KEY_NUMPAD3:
		return "numpad3";
	case KEY_NUMPAD4:
		return "numpad4";
	case KEY_NUMPAD5:
		return "numpad5";
	case KEY_NUMPAD6:
		return "numpad6";
	case KEY_NUMPAD7:
		return "numpad7";
	case KEY_NUMPAD8:
		return "numpad8";
	case KEY_NUMPAD9:
		return "numpad9";
	case KEY_MULTIPLY:
		return "numpad*";
	case KEY_ADD:
		return "numpad+";
	case KEY_SUBTRACT:
		return "numpad-";
	case KEY_DIVIDE:
		return "numpad/";
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
		return "f2";
	case KEY_NUMLOCK:
		return "numlock";
	case KEY_SCROLL:
		return "scroll";
	case KEY_SEPARATOR:
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
			return KEY_UP;
		else if (str.substr(0,4) == "down")
			return KEY_DOWN;
		else if (str.substr(0,3) == "esc")
			return KEY_ESCAPE;
		else if (str.substr(0,6) == "pageup")
			return KEY_PRIOR;
		else if (str.substr(0,8) == "pagedown")
			return KEY_NEXT;
		else if (str.substr(0,5) == "right")
			return KEY_RIGHT;
		else if (str.substr(0,4) == "left")
			return KEY_LEFT;
		else if (str.substr(0,5) == "space")
			return KEY_SPACE;
		else if (str.substr(0,6) == "mouse1")
			return KEY_LBUTTON;
		else if (str.substr(0,6) == "mouse2")
			return KEY_RBUTTON;
		else if (str.substr(0,6) == "mouse3")
			return KEY_MBUTTON;
		else if (str.substr(0,4) == "home")
			return KEY_HOME;
		else if (str.substr(0,3) == "end")
			return KEY_END;
		else if (str.substr(0,3) == "tab")
			return KEY_TAB;
		else if (str.substr(0,5) == "enter")
			return KEY_RETURN;
		else if (str.substr(0,6) == "insert")
			return KEY_INSERT;
		else if (str.substr(0,6) == "delete")
			return KEY_DELETE;
		else if (str.substr(0,7) == "control")
			return KEY_CONTROL;
		else if (str.substr(0,5) == "shift")
			return KEY_SHIFT;
		else if (str.substr(0,7) == "numpad0")
			return KEY_NUMPAD0;
		else if (str.substr(0,7) == "numpad1")
			return KEY_NUMPAD1;
		else if (str.substr(0,7) == "numpad2")
			return KEY_NUMPAD2;
		else if (str.substr(0,7) == "numpad3")
			return KEY_NUMPAD3;
		else if (str.substr(0,7) == "numpad4")
			return KEY_NUMPAD4;
		else if (str.substr(0,7) == "numpad5")
			return KEY_NUMPAD5;
		else if (str.substr(0,7) == "numpad6")
			return KEY_NUMPAD6;
		else if (str.substr(0,7) == "numpad7")
			return KEY_NUMPAD7;
		else if (str.substr(0,7) == "numpad8")
			return KEY_NUMPAD8;
		else if (str.substr(0,7) == "numpad9")
			return KEY_NUMPAD9;
		else if (str.substr(0,9) == "separator")
			return KEY_SEPARATOR;
		else if (str.substr(0,4) == "lwin")
			return KEY_LWIN;
		else if (str.substr(0,4) == "rwin")
			return KEY_RWIN;
		else if (str.substr(0,4) == "apps")
			return KEY_APPS;
		else if (str.substr(0,7) == "numpad*")
			return KEY_MULTIPLY;
		else if (str.substr(0,7) == "numpad+")
			return KEY_ADD;
		else if (str.substr(0,7) == "numpad/")
			return KEY_DIVIDE;
		else if (str.substr(0,7) == "numpad-")
			return KEY_SUBTRACT;
		else if (str.substr(0,6) == "scroll")
			return KEY_SCROLL;
		else if (str.substr(0,7) == "numlock")
			return KEY_NUMLOCK;
		else if (str.substr(0,5) == "pause")
			return KEY_PAUSE;
		else if (str.substr(0,8) == "capslock")
			return KEY_CAPITAL;
		


		/*uncomment this to enable f1 as a mappable key
		else if(str.substr(0,2) == "f1")
			return KEY_F1;
		*/

		else if (str.substr(0,2) == "f2")
			return KEY_F2;
		else if (str.substr(0,2) == "f3")
			return KEY_F3;
		else if (str.substr(0,2) == "f4")
			return KEY_F4;
		else if (str.substr(0,2) == "f5")
			return KEY_F5;
		else if (str.substr(0,2) == "f6")
			return KEY_F6;
		else if (str.substr(0,2) == "f7")
			return KEY_F7;
		else if (str.substr(0,2) == "f8")
			return KEY_F8;
		else if (str.substr(0,2) == "f9")
			return KEY_F9;
		else if (str.substr(0,2) == "f10")
			return KEY_F10;
		else if (str.substr(0,2) == "f11")
			return KEY_F11;
		else if (str.substr(0,2) == "f12")
			return KEY_F12;
		//Add Game specific keys here and e-mail headhunter45@hotmail.com subject OpenArena keys so I can add them please
		else if (str.substr(0,4) == "null")
			return (uint8)NULL;
		else
			return (uint8)NULL;
	}
	else
	{
		if(str[0] == '~' || str[0] == '`')
			return KEY_OEM_3;
		else if (str[0] == '?' || str[0] == '/')
            return KEY_OEM_2;
		else if (str[0] == '.' || str[0] == '>')
			return KEY_OEM_PERIOD;
		else if (str[0] == '+' || str[0] == '=')
			return KEY_OEM_PLUS;
		else if (str[0] == ';' || str[0] == ':')
			return KEY_OEM_1;
		else if (str[0] == ',' || str[0] == '<')
			return KEY_OEM_COMMA;
		else if (str[0] == '-' || str[0] == '_')
			return KEY_OEM_MINUS;
		else if (str[0] == '[' || str[0] == '{')
			return KEY_OEM_4;
		else if (str[0] == ']' || str[0] == '}')
			return KEY_OEM_6;
		else if (str[0] == '\\' || str[0] == '|')
			return KEY_OEM_5;
		else if (str[0] == '\'' || str[0] == '"')
			return KEY_OEM_7;
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
