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
#include <cstdio>
#ifdef WIN32
#include <windows.h>
#endif
#include <OpenGL/gl.h>

#include "bmp.h"
#ifdef WIN32
#pragma warning(disable : 4996)
#endif

namespace OpenArena {

#pragma pack(push, 1)

struct BITMAP_HEADER {
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
};

struct BITMAP_INFO {
  uint32_t size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bitCount;
  uint32_t compression;
  uint32_t sizeImage;
  uint32_t xPelsPerMeter;
  uint32_t yPelsPerMeter;
  uint32_t clrUsed;
  uint32_t clrImportant;
};

struct BITMAP_QUAD {
  uint8_t blue;
  uint8_t green;
  uint8_t red;
  uint8_t reserved;
};

#pragma pack(pop)

#define BITMAP_MAGIC 19778

void PrintBMPHeader(BITMAP_HEADER header) {
  printf("Header\n");
  printf("Type: %X\nSize: %X\nReserved1: %X\nReserved2: %X\nOffset:%X\n",
         header.type,
         header.size,
         header.reserved1,
         header.reserved2,
         header.offset);
}

void PrintBMPInfo(BITMAP_INFO info) {
  printf("Info\n");
  printf("Size: %X\nWidth: %X\nHeight:%X\n", info.size, info.width, info.height);
  printf("Planes: %X\nBitCount: %X\nCompression: %X\n", info.planes, info.bitCount, info.compression);
  printf(
      "SizeImage: %X\nXPelsPerMeter: %X\nYPelsPerMeter: %X\n", info.sizeImage, info.xPelsPerMeter, info.yPelsPerMeter);
  printf("ClrUsed: %X\nClrImportant: %X\n", info.clrUsed, info.clrImportant);
}

TextureImage* LoadBMP(const char* fn) {
  // If anything is not perfect return NULL after cleaning up our mess

  FILE* f = NULL;  // A pointer to our file structure

  // If our filename is null
  if (!fn) {
    return NULL;
  }

  // Try to open our file and if successfull...

  f = fopen(fn, "rb");
  if (f) {
    BITMAP_HEADER bmpHeader;
    BITMAP_INFO bmpInfo;
    BITMAP_QUAD* bmpPallette = NULL;
    uint32_t palletteEntries = 0;

    fread(&bmpHeader, sizeof(bmpHeader), 1, f);
    uint8_t t[2] = {1, 0};
    if (*((short*)t) != 1) {
      // If big endian reorder bytes
      bmpHeader.type = ((bmpHeader.type & 0xff00) >> 8) | ((bmpHeader.type & 0x00ff) << 8);
      bmpHeader.size = (bmpHeader.size & 0xff000000) >> 24 | (bmpHeader.size & 0x00ff0000) >> 8
                     | (bmpHeader.size & 0x0000ff00) << 8 | (bmpHeader.size & 0x000000ff) << 24;
      bmpHeader.reserved1 = ((bmpHeader.reserved1 & 0xff00) >> 8) | ((bmpHeader.reserved1 & 0x00ff) << 8);
      bmpHeader.reserved2 = ((bmpHeader.reserved2 & 0xff00) >> 8) | ((bmpHeader.reserved2 & 0x00ff) << 8);
      bmpHeader.offset = (bmpHeader.offset & 0xff000000) >> 24 | (bmpHeader.offset & 0x00ff0000) >> 8
                       | (bmpHeader.offset & 0x0000ff00) << 8 | (bmpHeader.offset & 0x000000ff) << 24;
    }

    fread(&bmpInfo, sizeof(bmpInfo), 1, f);
    if (*((short*)t) != 1) {
      // If big endian reorder bytes
      bmpInfo.size = (bmpInfo.size & 0xff000000) >> 24 | (bmpInfo.size & 0x00ff0000) >> 8
                   | (bmpInfo.size & 0x0000ff00) << 8 | (bmpInfo.size & 0x000000ff) << 24;
      bmpInfo.width = (bmpInfo.width & 0xff000000) >> 24 | (bmpInfo.width & 0x00ff0000) >> 8
                    | (bmpInfo.width & 0x0000ff00) << 8 | (bmpInfo.width & 0x000000ff) << 24;
      bmpInfo.height = (bmpInfo.height & 0xff000000) >> 24 | (bmpInfo.height & 0x00ff0000) >> 8
                     | (bmpInfo.height & 0x0000ff00) << 8 | (bmpInfo.height & 0x000000ff) << 24;
      bmpInfo.planes = ((bmpInfo.planes & 0xff00) >> 8) | ((bmpInfo.planes & 0x00ff) << 8);
      bmpInfo.bitCount = ((bmpInfo.bitCount & 0xff00) >> 8) | ((bmpInfo.bitCount & 0x00ff) << 8);
      bmpInfo.compression = (bmpInfo.compression & 0xff000000) >> 24 | (bmpInfo.compression & 0x00ff0000) >> 8
                          | (bmpInfo.compression & 0x0000ff00) << 8 | (bmpInfo.compression & 0x000000ff) << 24;
      bmpInfo.sizeImage = (bmpInfo.sizeImage & 0xff000000) >> 24 | (bmpInfo.sizeImage & 0x00ff0000) >> 8
                        | (bmpInfo.sizeImage & 0x0000ff00) << 8 | (bmpInfo.sizeImage & 0x000000ff) << 24;
      bmpInfo.xPelsPerMeter = (bmpInfo.xPelsPerMeter & 0xff000000) >> 24 | (bmpInfo.xPelsPerMeter & 0x00ff0000) >> 8
                            | (bmpInfo.xPelsPerMeter & 0x0000ff00) << 8 | (bmpInfo.xPelsPerMeter & 0x000000ff) << 24;
      bmpInfo.yPelsPerMeter = (bmpInfo.yPelsPerMeter & 0xff000000) >> 24 | (bmpInfo.yPelsPerMeter & 0x00ff0000) >> 8
                            | (bmpInfo.yPelsPerMeter & 0x0000ff00) << 8 | (bmpInfo.yPelsPerMeter & 0x000000ff) << 24;
      bmpInfo.clrUsed = (bmpInfo.clrUsed & 0xff000000) >> 24 | (bmpInfo.clrUsed & 0x00ff0000) >> 8
                      | (bmpInfo.clrUsed & 0x0000ff00) << 8 | (bmpInfo.clrUsed & 0x000000ff) << 24;
      bmpInfo.clrImportant = (bmpInfo.clrImportant & 0xff000000) >> 24 | (bmpInfo.clrImportant & 0x00ff0000) >> 8
                           | (bmpInfo.clrImportant & 0x0000ff00) << 8 | (bmpInfo.clrImportant & 0x000000ff) << 24;
    }

    if (bmpInfo.width < 0) {
      // This needs to be abstracted somehow
#ifdef WIN32
      MessageBox(NULL, "Image width is negative", "ERROR", MB_OK);
#endif
      fclose(f);
      return NULL;
    }

    if (bmpInfo.width % 4 != 0) {
      // This needs to be abstracted somehow
#ifdef WIN32
      MessageBox(NULL, "Image width must be a multiple of 8", "ERROR", MB_OK);
#endif
      fclose(f);
      return NULL;
    }

    if (bmpInfo.height < 0) {
      // This needs to be abstracted somehow
#ifdef WIN32
      MessageBox(NULL, "Image height is negative", "ERROR", MB_OK);
#endif
      fclose(f);
      return NULL;
    }

    if (bmpInfo.height % 4 != 0) {
      // This needs to be abstracted somehow
#ifdef WIN32
      MessageBox(NULL, "Image height must be a multiple of 8", "ERROR", MB_OK);
#endif
      fclose(f);
      return NULL;
    }

    if ((bmpInfo.bitCount != 8 && bmpInfo.bitCount != 24) || bmpInfo.compression != 0) {
      // This needs to be abstracted somehow
#ifdef WIN32
      MessageBox(NULL,
                 "Only 8 and 24 bit uncompressed windows bmp files are "
                 "currently supported",
                 "ERROR",
                 MB_OK);
#endif
      fclose(f);
      return NULL;
    }

    // Allocate memory for a TextureImage structure
    TextureImage* tex = new TextureImage;
    tex->sizeX = bmpInfo.width;
    tex->sizeY = bmpInfo.height;
    if (bmpInfo.bitCount >= 8) {
      tex->bpp = bmpInfo.bitCount >> 3;
    }
    tex->type = GL_RGB;
    uint32_t pixels = tex->sizeX * tex->sizeY;
    uint32_t bytes = pixels * tex->bpp;
    tex->data = new uint8_t[bytes];

    if (bmpInfo.bitCount == 8) {
      // Load the pallette
      palletteEntries = bmpInfo.bitCount << 8;
      bmpPallette = new BITMAP_QUAD[palletteEntries];
      fread(bmpPallette, sizeof(BITMAP_QUAD), palletteEntries, f);
    }

    fseek(f, bmpHeader.offset, SEEK_SET);
    fread(tex->data, bytes, 1, f);

    if (bmpInfo.bitCount == 8) {
      // Apply the pallette
      uint8_t* image = tex->data;
      tex->bpp = 24;
      bytes = pixels * tex->bpp;
      tex->data = new uint8_t[bytes];

      uint32_t i;
      uint32_t i2;
      for (i = 0; i < pixels; i++) {
        i2 = (i << 1) + 1;
        // Should make sure image[i] < palletteEntries
        tex->data[i2] = bmpPallette[image[i]].red;
        tex->data[i2 + 1] = bmpPallette[image[i]].blue;
        tex->data[i2 + 2] = bmpPallette[image[i]].green;
      }

      delete[] image;
      image = NULL;
    } else if (bmpInfo.bitCount == 24) {
      uint32_t i;
      uint8_t t;

      for (i = 0; i < bytes; i += 3) {
        t = tex->data[i];
        tex->data[i] = tex->data[i + 2];
        tex->data[i + 2] = t;
      }
    }
    return tex;
  }
  return NULL;
}
};  // End namespace OpenArena
