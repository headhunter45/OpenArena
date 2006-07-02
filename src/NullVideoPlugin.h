#pragma once
#include "VideoPlugin.h"

namespace OpenArena
{

	class NullVideoPlugin :
		public OpenArena::VideoPlugin
	{
	public:
		NullVideoPlugin(void);
	public:
		virtual ~NullVideoPlugin(void);
		virtual Window* CreateNewWindow(uint32 width, uint32 height, uint32 bpp = 32, bool fullscreen = false, const char* title = NULL);
	};

};
