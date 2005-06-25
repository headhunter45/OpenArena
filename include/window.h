#ifndef __window_h__
#define __window_h__

#include "screen.h"
#ifdef __linux
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#endif

namespace OpenArena
{
	class Window: public SCREEN
	{
	public:
		#ifdef __linux
		Display* display;
		int screen;
		::Window window;
		GLXContext hRC;
		XSetWindowAttributes attributes;
		bool doubleBuffered;
		XF86VidModeModeInfo vidMode;
		int x, y;
		#endif
	};
};

#endif
