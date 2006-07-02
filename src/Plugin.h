#pragma once

namespace OpenArena
{
	class Plugin
	{
	public:
		virtual ~Plugin(void){}
		enum Type {VideoPlugin, AudioPlugin, InputPlugin};
	};


};