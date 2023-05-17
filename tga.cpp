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
#include "tga.h"

#include <cstdio>
#include <memory>
#include <string>

#include "Logger.h"
#include "opengl.h"

// clang-format on

namespace OpenArena {
namespace {
using std::make_shared;
using std::shared_ptr;
using std::string;

struct TGAHeader {
  uint8_t Header[12];  // File Header To Determine File Type
};

struct TGA {
  uint8_t header[6];       // Holds The First 6 Useful Bytes Of The File
  uint32_t bytesPerPixel;  // Number Of BYTES Per Pixel (3 Or 4)
  uint32_t imageSize;      // Amount Of Memory Needed To Hold The Image
  uint32_t type;           // The Type Of Image, GL_RGB Or GL_RGBA
  uint32_t Height;         // Height Of Image
  uint32_t Width;          // Width Of Image
  uint32_t Bpp;            // Number Of BITS Per Pixel (24 Or 32)
};

const uint8_t uTGAcompare[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // Uncompressed TGA Header
const uint8_t cTGAcompare[12] = {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // Compressed TGA Header

}  // End namespace

shared_ptr<TargaImage> LoadUncompressedTGA(FILE*);  // Load an Uncompressed file
shared_ptr<TargaImage> LoadCompressedTGA(FILE*);    // Load a Compressed file

TargaImage::~TargaImage() {}

shared_ptr<TargaImage> TargaImage::FromFile(string filename) {
  const string method_name = "OpenArena::TargaImage::FromFile(string) ";
  FILE* file = nullptr;
  TGAHeader tga_header;
  if (filename.empty()) {
    Logger::LogError(method_name + "filename is empty");
    return nullptr;
  }

  // TODO: If our filename doesn't exist return null.

  fopen_s(&file, filename.c_str(), "rb");
  if (file == nullptr) {
    Logger::LogError(method_name + "unable to open file " + filename);
    return nullptr;
  }

  if (fread(&tga_header, sizeof(tga_header), 1, file) != 1) {
    Logger::LogError(method_name + "Could not read file header from file " + filename);
    fclose(file);
    return nullptr;
  }

  if (memcmp(uTGAcompare, &tga_header, sizeof(tga_header)) == 0) {
    return LoadUncompressedTGA(file);
  } else if (memcmp(cTGAcompare, &tga_header, sizeof(tga_header)) == 0) {
    return LoadCompressedTGA(file);
  } else {
    Logger::LogError(method_name + "TGA file must be type 2 or type 10");
    fclose(file);
    return nullptr;
  }
}

shared_ptr<TargaImage> LoadUncompressedTGA(FILE* file) {
  const string method_name = "OpenArena::TargaImage::<anonymous>::LoadUncompressedTGA(FILE*)";
  TGA tga;
  shared_ptr<TargaImage> image = make_shared<TargaImage>();

  if (fread(tga.header, sizeof(tga.header), 1, file) != 1) {
    Logger::LogError(method_name + "Cound not read info header");
    fclose(file);
    return nullptr;
  }

  image->bpp_ = tga.header[4];
  image->size_x_ = tga.header[3] * 256 + tga.header[2];
  image->size_y_ = tga.header[1] * 256 + tga.header[0];

  if ((image->size_x_ <= 0) || (image->size_y_ <= 0) || ((image->bpp_ != 24) && (image->bpp_ != 32))) {
    Logger::LogError(method_name + "Invalid texture information");
    fclose(file);
    return nullptr;
  }

  if (image->bpp_ == 24) {
    image->type_ = ImageBase::Type::RGB;
  } else {
    image->type_ = ImageBase::Type::RGBA;
  }

  int bytes_per_pixel = image->bpp_ / 8;
  int num_pixels = image->size_x_ * image->size_y_;
  int num_bytes = num_pixels * bytes_per_pixel;
  image->data_ = shared_ptr<uint8_t[]>(new uint8_t[num_bytes]);
  if (image->data_ == nullptr) {
    Logger::LogError(method_name + "Could not allocate memory for image");
    fclose(file);
    return nullptr;
  }

  if (fread(image->data_.get(), 1, num_bytes, file) != num_bytes) {
    Logger::LogError(method_name + "Could not read image data");
    fclose(file);
    return nullptr;
  }

  for (uint32_t cswap = 0; cswap < num_bytes; cswap += bytes_per_pixel) {
    image->data_[cswap] ^= image->data_[cswap + 2] ^= image->data_[cswap] ^= image->data_[cswap + 2];
  }

  fclose(file);
  return image;
}

shared_ptr<TargaImage> LoadCompressedTGA(FILE* file) {
  const std::string method_name = "OpenArena::TargaImage::<anonymous>::LoadCompressedTGA ";
  shared_ptr<TargaImage> image = make_shared<TargaImage>();
  TGA tga;

  if (fread(tga.header, sizeof(tga.header), 1, file) != 1) {
    Logger::LogError(method_name + "Could not read info header");
    fclose(file);
    return nullptr;
  }

  image->bpp_ = tga.header[4];
  image->size_x_ = tga.header[1] * 256 + tga.header[0];
  image->size_y_ = tga.header[3] * 256 + tga.header[2];

  if ((image->size_x_ <= 0) || (image->size_y_ <= 0) || ((image->bpp_ != 24) && (image->bpp_ != 32))) {
    Logger::LogError(method_name + "Invalid texture information");
    fclose(file);
    return nullptr;
  }
  int bytes_per_pixel = image->bpp_ / 8;
  int num_pixels = image->size_x_ * image->size_y_;
  int num_bytes = num_pixels * bytes_per_pixel;
  image->data_ = shared_ptr<uint8_t[]>(new uint8_t[num_bytes]);
  if (image->data_ == nullptr) {
    Logger::LogError(method_name + "Could not allocate memory for image");
    fclose(file);
    return nullptr;
  }
  // TODO: Abstract the RLE decoder to it's own file/class.
  uint32_t current_pixel = 0;
  uint32_t current_byte = 0;
  uint8_t* color_buffer = (uint8_t*)malloc(bytes_per_pixel);
  do {
    uint8_t chunk_header = 0;
    if (fread(&chunk_header, sizeof(uint8_t), 1, file) != 1) {
      Logger::LogError(method_name + "Could not read RLE header");
      fclose(file);
      return nullptr;
    }

    if (chunk_header < 128) {
      chunk_header++;
      for (uint16_t counter = 0; counter < chunk_header; counter++) {
        if (fread(color_buffer, 1, bytes_per_pixel, file) != bytes_per_pixel) {
          Logger::LogError(method_name + "Could not read image data.");
          fclose(file);
          return nullptr;
        }
        image->data_[current_byte] = color_buffer[2];
        image->data_[current_byte + 1] = color_buffer[1];
        image->data_[current_byte + 2] = color_buffer[0];
        if (bytes_per_pixel == 4) {
          image->data_[current_byte + 3] = color_buffer[3];
        }
        current_byte += bytes_per_pixel;
        current_pixel++;
        if (current_pixel > num_pixels) {
          Logger::LogError(method_name + "Too many pixels read.");
          fclose(file);
        }
      }
    } else {
      chunk_header -= 127;
      if (fread(color_buffer, 1, bytes_per_pixel, file) != bytes_per_pixel) {
        Logger::LogError(method_name + "Could not read from file.");
        fclose(file);
        return nullptr;
      }
      for (uint16_t counter = 0; counter < chunk_header; counter++) {
        image->data_[current_byte] = color_buffer[2];
        image->data_[current_byte + 1] = color_buffer[1];
        image->data_[current_byte + 2] = color_buffer[0];
        if (bytes_per_pixel == 4) {
          image->data_[current_byte + 3] = color_buffer[3];
        }
        current_byte += bytes_per_pixel;
        current_pixel++;
        if (current_pixel > num_pixels) {
          Logger::LogError(method_name + "Too many pixels read.");
          fclose(file);
          return nullptr;
        }
      }
    }
  } while (current_pixel < num_pixels);
  fclose(file);
  return image;
}
}  // End namespace OpenArena
