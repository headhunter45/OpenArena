#pragma once

#include "list.h"
#include "Plugin.h"
#include "VideoPlugin.h"

namespace OpenArena
{
	/**
	* Perhaps this class should be a singleton.
	*/
	/*!
	 * \brief
	 * Write brief comment for PluginManager here.
	 * 
	 * Write detailed description for PluginManager here.
	 * 
	 * \remarks
	 * Write remarks for PluginManager here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class PluginManager
	{
	private:
		list<Plugin*> _plugins;
	public:
		/**
		* Creates a new PluginManager object
		*/
		/*!
		 * \brief
		 * Write brief comment for PluginManager here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for PluginManager here.
		 * 
		 * \remarks
		 * Write remarks for PluginManager here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		PluginManager(void);
		/*!
		 * \brief
		 * Write brief comment for ~PluginManager here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~PluginManager here.
		 * 
		 * \remarks
		 * Write remarks for ~PluginManager here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		~PluginManager(void);

		/*!
		 * \brief
		 * Write brief comment for GetPluginsOfType here.
		 * 
		 * \param type
		 * Description of parameter type.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetPluginsOfType here.
		 * 
		 * \remarks
		 * Write remarks for GetPluginsOfType here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		list<Plugin*> GetPluginsOfType(Plugin::Type type);
		/*!
		 * \brief
		 * Write brief comment for GetDefaultVideoPlugin here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetDefaultVideoPlugin here.
		 * 
		 * \remarks
		 * Write remarks for GetDefaultVideoPlugin here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		VideoPlugin* GetDefaultVideoPlugin(void);
	};
};