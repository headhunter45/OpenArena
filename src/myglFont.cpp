////////////////////////////////////////////////////////////////////////////////
//
//	Module:		myglFont.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	06-19-2005
//	Editors:	None
//
//	Purpose:
//
//	Summary of Methods:
//	Global
//		-function name
//			description
//	blahClass
//		-function name
//			description
//
//	Summary of Properties:
//	blahClass
//		-property name
//			description
//
////////////////////////////////////////////////////////////////////////////////

#include "../include/myglFont.h"

GLFontClass::GLFontClass()
{
	status = 0;
	base = 0;
	texture = 0;
	screenWidth = 1;
	screenHeight = 1;
}

GLFontClass::~GLFontClass()
{
	FreeFont();
}

bool GLFontClass::BuildFont(const char* texName)
{
	FreeFont();

	if(LoadGLTexture(texName, texture, GL_NEAREST, GL_NEAREST))
	{	
		float x, y;
		base = glGenLists(256);
		glBindTexture(GL_TEXTURE_2D, texture);
		for(short i = 0; i<256; i++)
		{
			x = i%16/16.0f;
			y = i/16/16.0f;
			glNewList(base+i, GL_COMPILE);
			glBegin(GL_QUADS);
				glTexCoord2f(x, 1-y-0.0625f);
				glVertex2i(0,0);
				glTexCoord2f(x+0.0625f, 1-y-0.0625f);
				glVertex2i(16,0);
				glTexCoord2f(x+0.0625f, 1-y);
				glVertex2i(16,16);
				glTexCoord2f(x, 1-y);
				glVertex2i(0,16);
			glEnd();
			glTranslated(16,0,0);
			glEndList();
		}
		status = true;
	}
	return status;
}

bool GLFontClass::FreeFont()
{
	if(status)
	{
		glDeleteLists(base, 256);
		status = false;
	}
	return status;
}

void GLFontClass::Print(int x, int y, const char* str, unsigned int set)
{
	if(status)
	{
		if(set>1)
			set = 1;
		
		glBindTexture(GL_TEXTURE_2D, texture);
		//glDisable(GL_DEPTH_TEST);
		//glEnable(GL_BLEND);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0,screenWidth,0,screenHeight,-1,1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslated(x, y, 0);
		glListBase(base-32+(128*set));
		glCallLists(strlen(str), GL_BYTE, str);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		//glDisable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
	}
}

bool GLFontClass::Status()
{
	return status;
}

void GLFontClass::SetScreenDimensions(short x, short y)
{
	screenWidth = x;
	screenHeight = y;
}

void GLFontClass::SetScreenWidth(short x)
{
	screenWidth = x;
}

void GLFontClass::SetScreenHeight(short y)
{
	screenHeight = y;
}

short GLFontClass::ScreenWidth()
{
	return screenWidth;
}

short GLFontClass::ScreenHeight()
{
	return screenHeight;
}
