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
	case VK_UP:
		return "up";
	case VK_DOWN:
		return "down";
	case VK_LEFT:
		return "left";
	case VK_RIGHT:
		return "right";
	case VK_PRIOR:
		return "pageup";
	case VK_NEXT:
		return "pagedown";
	case VK_SPACE:
		return "space";
	case VK_LBUTTON:
		return "mouse1";
	case VK_RBUTTON:
		return "mouse2";
	case VK_MBUTTON:
		return "mouse3";
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
		return toupper(str[0]);
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
			while (!isspace(str[++length]) && length <= maxLength);

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