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
#ifndef __bmp_h__
#define __bmp_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "texture.h"

namespace OpenArena{
	/**
	 * \brief
	 * Loads a bitmap (*.bmp) file and returns a pointer to a TextureImage object.
	 * 
	 * \param filename
	 * The path to the file to open.
	 * 
	 * \returns
	 * A pointer to the created TextureImage object.
	 * 
	 * \remarks
	 * Will be replaced with an actual class soon
	 * 
	 * \see
	 */
	TextureImage* LoadBMP(const char* Filename);
};

#endif
