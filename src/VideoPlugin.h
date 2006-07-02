#pragma once
#include "Plugin.h"
#include "window.h"
#include "datatypes.h"

namespace OpenArena
{
	class VideoPlugin :public Plugin
	{
	public:
	public:
		virtual ~VideoPlugin(){}
		virtual Window* CreateNewWindow(uint32 width,
			uint32 height, 
			uint32 bpp = 32, 
			bool fullscreen = false, 
			const char* title = NULL) = 0;
	};
};