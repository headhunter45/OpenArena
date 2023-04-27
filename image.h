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

#include <cstdint>
#if defined HAVE_CONFIG_H
#include "config.h"
#endif

namespace OpenArena {
/*!
 * \brief
 * Write brief comment for Image here.
 *
 * Write detailed description for Image here.
 *
 * \remarks
 * Write remarks for Image here.
 *
 * \see
 * Separate items with the '|' character.
 */
class Image {
 public:
  // RGB should equal GL_RGB;
  enum Type { Type_RGB };

  /*!
   * \brief
   * Write brief comment for GetImageData here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for GetImageData here.
   *
   * \remarks
   * Write remarks for GetImageData here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual uint8_t* GetImageData() const = 0;
  /*!
   * \brief
   * Write brief comment for GetBitsPerPixel here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for GetBitsPerPixel here.
   *
   * \remarks
   * Write remarks for GetBitsPerPixel here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual uint32_t GetBitsPerPixel() const = 0;
  /*!
   * \brief
   * Write brief comment for GetBytesPerPixel here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for GetBytesPerPixel here.
   *
   * \remarks
   * Write remarks for GetBytesPerPixel here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual uint32_t GetBytesPerPixel() const = 0;
  /*!
   * \brief
   * Write brief comment for GetWidth here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for GetWidth here.
   *
   * \remarks
   * Write remarks for GetWidth here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual uint32_t GetWidth() const = 0;
  /*!
   * \brief
   * Write brief comment for GetHeight here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for GetHeight here.
   *
   * \remarks
   * Write remarks for GetHeight here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual uint32_t GetHeight() const = 0;
  /*!
   * \brief
   * Write brief comment for GetType here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for GetType here.
   *
   * \remarks
   * Write remarks for GetType here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual Image::Type GetType() const = 0;

  /*!
   * \brief
   * Write brief comment for ~Image here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for ~Image here.
   *
   * \remarks
   * Write remarks for ~Image here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual ~Image(void) {}
};
}  // End namespace OpenArena

#endif  // End !defined(OpenArena__image_h__)
