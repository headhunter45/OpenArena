#pragma once

#include "list.h"
#include "Plugin.h"
#include "VideoPlugin.h"

namespace OpenArena
{
	/**
	* Perhaps this class should be a singleton.
	*/
	class PluginManager
	{
	private:
		list<Plugin*> _plugins;
	public:
		/**
		* Creates a new PluginManager object
		*/
		PluginManager(void);
		~PluginManager(void);

		list<Plugin*> GetPluginsOfType(Plugin::Type type);
		VideoPlugin* GetDefaultVideoPlugin(void);
	};
};