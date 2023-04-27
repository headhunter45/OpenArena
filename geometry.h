/***************************************************************************
 *   Copyright (C) 2001-2023 by Tom Hicks                                  *
 *   headhunter3@gmail.com                                                 *
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
#ifndef OpenArena__geometry_h__
#define OpenArena__geometry_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "myglTexture.h"
#include "vector.h"

namespace OpenArena {
class Vertex {
 public:
  Vec3f coordinates;
  Vec2f textureCoordinates;
};

/*!
 * \brief
 * Write brief comment for Triangle here.
 *
 * Write detailed description for Triangle here.
 *
 * \remarks
 * Write remarks for Triangle here.
 *
 * \see
 * Separate items with the '|' character.
 */
class Triangle {
 public:
  Texture texture;
  uint32_t texID;
  Vertex vertecies[3];
  //		Vec3f vertecies[3];
  //		Vec2f texCoords[3];
  Vec3f normal;
};

}  // End namespace OpenArena

#endif  // End !defined(OpenArena__geometry_h__)
