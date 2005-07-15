#include "../include/screen.h"

namespace OpenArena
{
	Screen::Screen()
	{
		_width=640;
		_height=480;
		_colorDepth=16;
		_fullscreen=false;
		_name = "";
	}

	int Screen::GetWidth()
	{
		return _width;
	}
    
	int Screen::GetHeight()
	{
		return _height;
	}

	int Screen::GetColorDepth()
	{
		return _colorDepth;
	}

	bool Screen::GetFullscreen()
	{
		return _fullscreen;
	}

	const char* Screen::GetName()
	{
		return _name.c_str();
	}

	void Screen::SetWidth(int width)
	{
		_width = width;
	}

	void Screen::SetHeight(int height)
	{
		_height = height;
	}

	void Screen::Resize(int width, int height)
	{
		_width = width;
		_height = height;
	}

	void Screen::SetColorDepth(int colorDepth)
	{
		_colorDepth = colorDepth;
	}

	void Screen::SetFullscreen(bool status)
	{
		_fullscreen = status;
	}

	void Screen::ToggleFullscreen()
	{
		_fullscreen = !_fullscreen;
	}

	void Screen::SetName(const char* name)
	{
		_name = name;
	}

	void Screen::SetName(string name)
	{
		_name = name;
	}
};
