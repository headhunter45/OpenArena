#ifndef __glPrint_h__
#define __glPrint_h__

#include "mygl.h"

class GLFontClass
{
private:
	short screenWidth;
	short screenHeight;
	unsigned int base;
	unsigned int texture;
	bool status;

public:
	GLFontClass();
	~GLFontClass();
	bool BuildFont(const char*);
	bool FreeFont();
	void Print(int, int, const char*, unsigned int = 0);
	bool Status();
	void SetScreenDimensions(short, short);
	void SetScreenWidth(short);
	void SetScreenHeight(short);
	short ScreenWidth();
	short ScreenHeight();
};

#endif
