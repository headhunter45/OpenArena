#ifndef __screen_h__
#define __screen_h__
#include <string>

using namespace std;

class SCREEN
{
public:
	SCREEN()
	{
		width=640;
		height=480;
		bpp=16;
		fullscreen=false;
		name = "";
	}

	short width;
	short height;
	char bpp;
	bool fullscreen;
	string name;


};

#endif