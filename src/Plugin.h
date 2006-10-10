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
#ifndef __Plugin_h__
#define __Plugin_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Plugin here.
	 * 
	 * Write detailed description for Plugin here.
	 * 
	 * \remarks
	 * Write remarks for Plugin here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Plugin
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for ~Plugin here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~Plugin here.
		 * 
		 * \remarks
		 * Write remarks for ~Plugin here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual ~Plugin(void){}
		/*!
		 * \brief
		 * Write brief comment for InputPlugin here.
		 */
		enum Type {VideoPlugin, AudioPlugin, InputPlugin};
	};


};

#endif
