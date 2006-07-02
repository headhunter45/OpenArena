#include "PluginManager.h"
#include "NullVideoPlugin.h"

namespace OpenArena
{
	PluginManager::PluginManager(void)
	{
	}

	PluginManager::~PluginManager(void)
	{
	}
	
	list<Plugin*> PluginManager::GetPluginsOfType(Plugin::Type type)
	{
		return list<Plugin*>();
	}
	VideoPlugin* PluginManager::GetDefaultVideoPlugin(void)
	{
		return new NullVideoPlugin();
	}


};

