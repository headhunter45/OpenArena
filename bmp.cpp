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

// clang-format off
#include "bmp.h"
#include <cstdint>
#include <cstdio>
#include <memory>
#include "Logger.h"
#include "opengl.h"

// clang-format on

namespace OpenArena {
namespace {
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::to_string;
}  // End namespace

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

uint16_t SwapBytes(uint16_t value) {
  return ((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8);
}

uint32_t SwapBytes(uint32_t value) {
  return ((value & 0xFF000000) >> 24) | ((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) << 8)
       | ((value & 0x000000FF) << 24);
}

void PrintBMPHeader(BITMAP_HEADER header) {
  printf("Header\n");
  printf("Type: %X\nSize: %X\nReserved1: %X\nReserved2: %X\nOffset:%X\n", header.type, header.size, header.reserved1,
         header.reserved2, header.offset);
}

void PrintBMPInfo(BITMAP_INFO info) {
  printf("Info\n");
  printf("Size: %X\nWidth: %X\nHeight:%X\n", info.size, info.width, info.height);
  printf("Planes: %X\nBitCount: %X\nCompression: %X\n", info.planes, info.bitCount, info.compression);
  printf("SizeImage: %X\nXPelsPerMeter: %X\nYPelsPerMeter: %X\n", info.sizeImage, info.xPelsPerMeter,
         info.yPelsPerMeter);
  printf("ClrUsed: %X\nClrImportant: %X\n", info.clrUsed, info.clrImportant);
}

BitmapImage::~BitmapImage() {}

shared_ptr<BitmapImage> BitmapImage::FromFile(string filename) {
  const string method_name = "OpenArena::BitmapImage::FromFile(string) ";
  // TODO: Switch to fstream later.
  FILE* file = nullptr;

  Logger::LogDebug("In " + method_name);

  // If anything is not perfect return null after cleaning up our mess.

  // If our filename is empty return null.
  if (filename.empty()) {
    Logger::LogError(method_name + "filename is empty");
    return nullptr;
  }

  Logger::LogDebug(method_name + "filename is " + filename);

  // TODO: If our filename doesn't exist return null.

  // Try to open our file and if successfull...
  fopen_s(&file, filename.c_str(), "rb");
  if (file == nullptr) {
    Logger::LogError(method_name + "unable to open file " + filename);
    return nullptr;
  }
  Logger::LogDebug(method_name + "opened file with handle " + to_string((uint64_t)file));
  BITMAP_HEADER bmpHeader;
  BITMAP_INFO bmpInfo;
  BITMAP_QUAD* bmpPallette = nullptr;
  uint32_t palletteEntries = 0;

  if (fread(&bmpHeader, sizeof(bmpHeader), 1, file) != 1) {
    Logger::LogError(method_name + "Failed to read bitmap header.");
    fclose(file);
    return nullptr;
  }

  // TODO: Come up with a better endianness check.
  uint8_t t[2] = {1, 0};
  if (*((short*)t) != 1) {
    // If big endian reorder bytes.
    bmpHeader.type = SwapBytes(bmpHeader.type);
    bmpHeader.size = SwapBytes(bmpHeader.size);
    bmpHeader.reserved1 = SwapBytes(bmpHeader.reserved1);
    bmpHeader.reserved2 = SwapBytes(bmpHeader.reserved2);
    bmpHeader.offset = SwapBytes(bmpHeader.offset);
  }

  if (fread(&bmpInfo, sizeof(bmpInfo), 1, file) != 1) {
    Logger::LogError(method_name + "Unable to read BITMAP_INFO.");
    fclose(file);
    return nullptr;
  }
  if (*((short*)t) != 1) {
    // If big endian reorder bytes.
    bmpInfo.size = SwapBytes(bmpInfo.size);
    bmpInfo.width = SwapBytes(bmpInfo.width);
    bmpInfo.height = SwapBytes(bmpInfo.height);
    bmpInfo.planes = SwapBytes(bmpInfo.planes);
    bmpInfo.bitCount = SwapBytes(bmpInfo.bitCount);
    bmpInfo.compression = SwapBytes(bmpInfo.compression);
    bmpInfo.sizeImage = SwapBytes(bmpInfo.sizeImage);
    bmpInfo.xPelsPerMeter = SwapBytes(bmpInfo.xPelsPerMeter);
    bmpInfo.yPelsPerMeter = SwapBytes(bmpInfo.yPelsPerMeter);
    bmpInfo.clrUsed = SwapBytes(bmpInfo.clrUsed);
    bmpInfo.clrImportant = SwapBytes(bmpInfo.clrImportant);
  }

  if (bmpInfo.width < 0) {
    Logger::LogError("Image width is negative.");
    fclose(file);
    return nullptr;
  }

  if (bmpInfo.width % 4 != 0) {
    Logger::LogError("Image width must be a multiple of 8.");
    fclose(file);
    return nullptr;
  }

  if (bmpInfo.height < 0) {
    Logger::LogError("Image height is negative.");
    fclose(file);
    return nullptr;
  }

  if (bmpInfo.height % 4 != 0) {
    Logger::LogError("Image height must be a multiple of 8.");
    fclose(file);
    return nullptr;
  }

  if ((bmpInfo.bitCount != 8 && bmpInfo.bitCount != 24) || bmpInfo.compression != 0) {
    Logger::LogError("Only 8 and 24 bit uncompressed windows bmp files are currently supported.");
    fclose(file);
    return nullptr;
  }

  // Allocate memory for our image data.
  shared_ptr<BitmapImage> bmp = make_shared<BitmapImage>();
  bmp->size_x_ = bmpInfo.width;
  bmp->size_y_ = bmpInfo.height;
  bmp->bpp_ = bmpInfo.bitCount;
  int bytes_per_pixel = bmp->bpp_ / 8;
  bmp->type_ = Type::RGB;
  int num_pixels = bmp->size_x_ * bmp->size_y_;
  int num_bytes = num_pixels * bytes_per_pixel;
  Logger::LogDebug("allocating " + to_string(num_bytes) + " bytes for pixel data");
  bmp->data_ = shared_ptr<uint8_t[]>(new uint8_t[num_bytes]);
  if (bmpInfo.bitCount == 8) {
    Logger::LogDebug("image has a pallette");
    // Load the pallette
    palletteEntries = bmpInfo.bitCount << 8;
    bmpPallette = new BITMAP_QUAD[palletteEntries];
    if (fread(bmpPallette, sizeof(BITMAP_QUAD), palletteEntries, file) != palletteEntries) {
      Logger::LogError(method_name + "Wrong number of pallette entries read.");
      fclose(file);
      return nullptr;
    }
  }
  Logger::LogDebug("Loading bitmap data from file.");
  fseek(file, bmpHeader.offset, SEEK_SET);
  if (fread(bmp->data_.get(), num_bytes, 1, file) != 1) {
    Logger::LogError(method_name + "Failed to read the expected number of pixels from the file.");
    fclose(file);
    return nullptr;
  }

  Logger::LogDebug("Processing image data.");
  if (bmpInfo.bitCount == 8) {
    // Apply the pallette
    shared_ptr<uint8_t[]> image = bmp->data_;
    bmp->bpp_ = 24;
    bytes_per_pixel = bmp->bpp_ / 8;
    num_bytes = num_pixels * bytes_per_pixel;
    bmp->data_ = shared_ptr<uint8_t[]>(new uint8_t[num_bytes]);
    uint32_t i;
    uint32_t i2;
    for (i = 0; i < num_pixels; i++) {
      i2 = (i << 1) + 1;
      // Should make sure image[i] < palletteEntries
      bmp->data_[i2] = bmpPallette[image[i]].red;
      bmp->data_[i2 + 1] = bmpPallette[image[i]].blue;
      bmp->data_[i2 + 2] = bmpPallette[image[i]].green;
    }
    image = nullptr;
  } else if (bmpInfo.bitCount == 24) {
    uint32_t i;
    uint8_t t;
    for (i = 0; i < num_bytes; i += 3) {
      t = bmp->data_[i];
      bmp->data_[i] = bmp->data_[i + 2];
      bmp->data_[i + 2] = t;
    }
  }
  return bmp;
}
};  // End namespace OpenArena
