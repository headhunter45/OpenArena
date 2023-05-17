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
#include "image.h"
#include <memory>
#include <string>
#include "Logger.h"
#include "opengl.h"
// clang-format off

namespace OpenArena {
namespace {
using std::shared_ptr;
using std::string;
using std::to_string;
} // End namespace

ImageBase::ImageBase() : data_(nullptr), bpp_(0), size_x_(0), size_y_(0), type_(Type::Unknown) {}

ImageBase::~ImageBase() {}

shared_ptr<uint8_t[]> ImageBase::GetImageData() const {
  return data_;
}

uint32_t ImageBase::GetBitsPerPixel() const {
  return bpp_;
}

uint32_t ImageBase::GetBytesPerPixel() const {
  return bpp_ / 8;
}

uint32_t ImageBase::GetWidth() const {
  return size_x_;
}

uint32_t ImageBase::GetHeight() const {
  return size_y_;
}

ImageBase::Type ImageBase::GetType() const {
  return type_;
}

TextureImage* ImageBase::ToTextureImage() const {
  const string method_name = "OpenArena::ImageBase::ToTextureImage() ";
  Logger::LogDebug("In " + method_name);
  TextureImage* p_texture_image = new TextureImage();
  Logger::LogDebug(method_name + "p_texture_image is " + (p_texture_image ? "not null" : "null"));

  int num_pixels = size_x_ * size_y_;
  int num_bytes = num_pixels * bpp_ / 8;

  p_texture_image->bpp = bpp_;
  Logger::LogToDo(method_name + "make TextureImage::data a shared_prt<uint8_t[]> instead of a uint8_t*");
  p_texture_image->data = new uint8_t[num_bytes];
  p_texture_image->sizeX = size_x_;
  p_texture_image->sizeY = size_y_;
  p_texture_image->type = GL_RGB;
  Logger::LogDebug(method_name + "width: " + to_string(size_x_) + ", height: " + to_string(size_y_)
                   + ", bpp: " + to_string(bpp_));
  Logger::LogDebug(method_name + "New image data array is " + (p_texture_image->data ? "not null" : "null"));
  Logger::LogDebug(method_name + "Copying " + to_string(num_pixels) + " pixels from " + to_string(num_bytes)
                   + " bytes");

  for (int i = 0; i < num_bytes; i++) {
    // Logger::LogDebug(method_name + "copying the " + to_string(i) + "th byte");
    p_texture_image->data[i] = data_[i];
  }

  Logger::LogDebug("Leaving " + method_name);
  return p_texture_image;
}
}  // End namespace OpenArena
