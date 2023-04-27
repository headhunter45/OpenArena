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
#ifndef OpenArena__tga_h__
#define OpenArena__tga_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdio>
#include <string>

#include "texture.h"

namespace OpenArena {
/*!
 * \brief
 * Write brief comment for TGAHeader here.
 *
 * Write detailed description for TGAHeader here.
 *
 * \remarks
 * Write remarks for TGAHeader here.
 *
 * \see
 * Separate items with the '|' character.
 */
struct TGAHeader {
  uint8_t Header[12];  // File Header To Determine File Type
};

/*!
 * \brief
 * Write brief comment for TGA here.
 *
 * Write detailed description for TGA here.
 *
 * \remarks
 * Write remarks for TGA here.
 *
 * \see
 * Separate items with the '|' character.
 */
struct TGA {
  uint8_t header[6];       // Holds The First 6 Useful Bytes Of The File
  uint32_t bytesPerPixel;  // Number Of BYTES Per Pixel (3 Or 4)
  uint32_t imageSize;      // Amount Of Memory Needed To Hold The Image
  uint32_t type;           // The Type Of Image, GL_RGB Or GL_RGBA
  uint32_t Height;         // Height Of Image
  uint32_t Width;          // Width Of Image
  uint32_t Bpp;            // Number Of BITS Per Pixel (24 Or 32)
};

/*!
 * \brief
 * Write brief comment for LoadTGA here.
 *
 * \param filename
 * Description of parameter filename.
 *
 * \returns
 * Write description of return value here.
 *
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 *
 * Write detailed description for LoadTGA here.
 *
 * \remarks
 * Write remarks for LoadTGA here.
 *
 * \see
 * Separate items with the '|' character.
 */
TextureImage* LoadTGA(const char* filename);

const uint8_t uTGAcompare[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // Uncompressed TGA Header
const uint8_t cTGAcompare[12] = {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // Compressed TGA Header
TextureImage* LoadUncompressedTGA(FILE*);                               // Load an Uncompressed file
TextureImage* LoadCompressedTGA(FILE*);                                 // Load a Compressed file
};                                                                      // namespace OpenArena
#endif
