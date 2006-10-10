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
#ifndef __texture_h__
#define __texture_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for TextureImage here.
	 * 
	 * Write detailed description for TextureImage here.
	 * 
	 * \remarks
	 * Write remarks for TextureImage here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class TextureImage
	{
	public:
		unsigned char* data;
		unsigned int bpp;
		unsigned int sizeX;
		unsigned int sizeY;
		unsigned int type;
	};
};
#endif
