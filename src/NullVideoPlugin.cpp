#include "NullVideoPlugin.h"
namespace OpenArena
{

	NullVideoPlugin::NullVideoPlugin(void)
	{
	}

	NullVideoPlugin::~NullVideoPlugin(void)
	{
	}

	OpenArena::Window* NullVideoPlugin::CreateNewWindow(uint32 width, uint32 height, uint32 bpp, bool fullscreen, const char* title)
	{
		return new OpenArena::Window();
	}

};