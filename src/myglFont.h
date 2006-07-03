#ifndef __glPrint_h__
#define __glPrint_h__

#include "mygl.h"

namespace OpenArena
{
	class Font
	{
	private:
		short screenWidth;
		short screenHeight;
		unsigned int base;
		GLuint texture;
		bool status;
	
	public:
		Font();
		~Font();
		bool BuildFont(const char*);
		bool FreeFont();
		void Print(int, int, const char*, unsigned int = 0);
		bool Loaded();
		void SetScreenDimensions(short, short);
		void SetScreenWidth(short);
		void SetScreenHeight(short);
		short ScreenWidth();
		short ScreenHeight();
	};
};
#endif
