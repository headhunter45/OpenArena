#ifndef __window_h__
#define __window_h__

#include "screen.h"
#ifdef __linux
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#endif
#ifdef WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace OpenArena
{
	typedef void (*ResizeFunc)(GLsizei width, GLsizei height);
	typedef int (*InitFunc)();

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
	private:
#endif
#ifdef WIN32
		HGLRC glContext;
		HWND window;
	private:
		HDC deviceContext;
		HINSTANCE instance;
#endif
		

	public:
		Window();
		~Window();
		void Close();
		bool Open();
		bool Open(string title, int width, int height, int bits, bool fullscreenflag);	//make that string a const char* after this works
		void SetOnInit(InitFunc function);
		void SetOnResize(ResizeFunc function);
		void SwapBuffers();

	private:
		ResizeFunc OnResize;
		InitFunc OnInit;
	};

	void DefaultResize(GLsizei width, GLsizei height);
	int DefaultInit();
};

#ifdef WIN32
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif

#endif
