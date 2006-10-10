/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks   *
 *   tomhicks@cse.buffalo.edu   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef __PluginManager_h__
#define __PluginManager_h___

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

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

#endif
