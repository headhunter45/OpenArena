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

#ifndef OpenArena__image_h__
#define OpenArena__image_h__
// clang-format off
#include "config.h"
#include <cstdint>
#include <memory>
#include "texture.h"

// clang-format on

namespace OpenArena {

class ImageBase {
 public:
  enum Type { Unknown, RGB, RGBA };

  ImageBase();
  virtual ~ImageBase();
  virtual std::shared_ptr<uint8_t[]> GetImageData() const;
  virtual uint32_t GetBitsPerPixel() const;
  virtual uint32_t GetBytesPerPixel() const;
  virtual uint32_t GetWidth() const;
  virtual uint32_t GetHeight() const;
  virtual ImageBase::Type GetType() const;
  virtual TextureImage* ToTextureImage() const;

  std::shared_ptr<uint8_t[]> data_;
  uint32_t bpp_;
  uint32_t size_x_;
  uint32_t size_y_;
  Type type_;

 private:
};

class Image {
 public:
  // RGB should equal GL_RGB;
  enum Type { Type_RGB, Type_RGBA };

  virtual uint8_t* GetImageData() const = 0;
  virtual uint32_t GetBitsPerPixel() const = 0;
  virtual uint32_t GetBytesPerPixel() const = 0;
  virtual uint32_t GetWidth() const = 0;
  virtual uint32_t GetHeight() const = 0;
  virtual Image::Type GetType() const = 0;

  virtual ~Image(void) {}
};
}  // End namespace OpenArena

#endif  // End !defined(OpenArena__image_h__)
