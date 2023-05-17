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

#ifndef OpenArena__myglTexture_h__
#define OpenArena__myglTexture_h__
// clang-format off
#include "config.h"
#include <string>
#include "mygl.h"

// clang-format on

namespace OpenArena {
class Texture {
 public:
  Texture();
  ~Texture();
  std::string Filename() const;
  uint32_t ID() const;
  bool Load(std::string filename);
  bool Load(std::string filename, uint32_t min, uint32_t mag);
  void Free();
  bool Loaded() const;
  bool operator<(const Texture&) const;
  bool operator<=(const Texture&) const;
  bool operator==(const Texture&) const;
  bool operator!=(const Texture&) const;
  bool operator>=(const Texture&) const;
  bool operator>(const Texture&) const;

 private:
  uint32_t minFilter;
  uint32_t magFilter;
  std::string filename;
  uint32_t id;
};

extern Texture kUnknownTexture;
}  // End namespace OpenArena
#endif  // End !defined(OpenArena__myglTexture_h__)
