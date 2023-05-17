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
#include "mygl.h"
#include "Logger.h"
#include "bmp.h"
#include "strmanip.h"
#include "texture.h"
#include "tga.h"

// clang-format on

namespace OpenArena {
namespace {
using std::shared_ptr;
using std::string;
}  // End namespace

void FreeGLTexture(GLuint& texture) {
  glDeleteTextures(1, &texture);
}

bool LoadGLTexture(string fn, GLuint& texture, GLuint mag, GLuint min) {
  string method_name = "OpenArena::LoadGLTexture(string, GLuint&, GLuint, GLuint) ";
  if (Right(tolower(fn), 4) == ".bmp") {
    Logger::LogDebug(method_name + "Loading a bitmap.");
    shared_ptr<BitmapImage> bmp = BitmapImage::FromFile(fn);
    Logger::LogDebug((string) "bitmap is " + (bmp ? "not null" : "null"));
    TextureImage* texImage = bmp->ToTextureImage();
    if (texImage) {
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, texImage->sizeX, texImage->sizeY, 0, texImage->type, GL_UNSIGNED_BYTE,
                   texImage->data);

      if (texImage)  // Just in case somehow the file was empty or unloadable
      {
        if (texImage->data) free(texImage->data);
        free(texImage);
      }
      return true;
    } else {
      return false;
    }
  } else if (Right(tolower(fn), 4) == ".tga") {
    Logger::LogDebug(method_name + "Loading a tga file.");
    shared_ptr<TargaImage> tga = TargaImage::FromFile(fn);
    Logger::LogDebug(method_name + "tga is " + (tga ? "not null" : "null"));
    TextureImage* texImage = tga->FromFile(fn)->ToTextureImage();
    Logger::LogDebug(method_name + "texImage is " + (texImage ? "not null" : "null"));
    if ((texImage)) {
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, texImage->sizeX, texImage->sizeY, 0, texImage->type, GL_UNSIGNED_BYTE,
                   texImage->data);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      if (texImage)  // Just in case somehow the file was empty or unloadable
      {
        if (texImage->data) free(texImage->data);
        free(texImage);
      }
      Logger::LogDebug(method_name + "returning true");
      return true;
    } else {
      Logger::LogDebug(method_name + "returning false from 1");
      return false;
    }
  } else {
    Logger::LogDebug(method_name + "returning false from 2");
    return false;
  }
}

OpenArena::Window* g_Screen = new OpenArena::Window();

}  // End namespace OpenArena
