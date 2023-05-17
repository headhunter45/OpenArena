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
#include "myglTexture.h"
#include <string>
#include "Logger.h"

// clang-format on

namespace OpenArena {
namespace {
using std::string;
using std::to_string;
}  // End namespace

Texture::Texture() {
  Logger::LogDebug("OpenArena::Texture::Texture() Making a new unloaded texture.");
  id = 0xFFFFFFFF;
  filename = "";
  minFilter = GL_LINEAR;
  magFilter = GL_LINEAR;
}

Texture::~Texture() {
  Free();
}

string Texture::Filename() const {
  return filename;
}

GLuint Texture::ID() const {
  return id;
}

bool Texture::Loaded() const {
  return filename != "";
}

bool Texture::Load(string fn) {
  const string method_name = "OpenArena::Texture::Load ";
  Logger::LogDebug(method_name + "Loading texture from " + fn);
  if (Loaded()) {
    Logger::LogDebug(method_name + "Freeing old texture " + filename);
    Free();
  }

  if (LoadGLTexture(fn.c_str(), id, minFilter, magFilter)) {
    Logger::LogDebug(method_name + "Texture load successful");
    filename = fn;
    return true;
  } else {
    Logger::LogError(method_name + "error while loading texture from " + fn
                     + ", with min_filter = " + to_string(minFilter) + ", and mag_filter = " + to_string(magFilter));
    id = 0xFFFFFFFF;
    return false;
  }
}

bool Texture::Load(string fn, GLuint min, GLuint mag) {
  string method_name = "OpenArena::Texture::Load(string, GLuint, GLuint) ";
  Logger::LogDebug(method_name + "Loading texture from " + fn);
  if (Loaded()) {
    Logger::LogDebug(method_name + "Freeing old texture " + fn);
    Free();
  }

  if (LoadGLTexture(fn.c_str(), id, min, mag)) {
    Logger::LogDebug(method_name + "Texture load successful");
    filename = fn;
    minFilter = min;
    magFilter = mag;
    return true;
  } else {
    Logger::LogError(method_name + "error while loading texture from " + fn + ", with min_filter = " + to_string(min)
                     + ", and mag_filter = " + to_string(mag));
    id = 0xFFFFFFFF;
    return false;
  }
}

void Texture::Free() {
  if (Loaded()) {
    FreeGLTexture(id);
    minFilter = GL_LINEAR;
    magFilter = GL_LINEAR;
    filename = "";
    id = 0xFFFFFFFF;
  }
}

bool Texture::operator<(const Texture& rtOp) const {
  return id < rtOp.id;
}

bool Texture::operator<=(const Texture& rtOp) const {
  return id <= rtOp.id;
}

bool Texture::operator==(const Texture& rtOp) const {
  return id == rtOp.id;
}

bool Texture::operator!=(const Texture& rtOp) const {
  return id != rtOp.id;
}

bool Texture::operator>=(const Texture& rtOp) const {
  return id >= rtOp.id;
}

bool Texture::operator>(const Texture& rtOp) const {
  return id > rtOp.id;
}

Texture kUnknownTexture = Texture();

}  // End namespace OpenArena
