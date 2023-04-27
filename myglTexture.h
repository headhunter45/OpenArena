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

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>

#include "mygl.h"

using namespace std;

namespace OpenArena {
/*!
 * \brief
 * Write brief comment for Texture here.
 *
 * Write detailed description for Texture here.
 *
 * \remarks
 * Write remarks for Texture here.
 *
 * \see
 * Separate items with the '|' character.
 */
class Texture {
 public:
  /*!
   * \brief
   * Write brief comment for Texture here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for Texture here.
   *
   * \remarks
   * Write remarks for Texture here.
   *
   * \see
   * Separate items with the '|' character.
   */
  Texture();
  /*!
   * \brief
   * Write brief comment for ~Texture here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for ~Texture here.
   *
   * \remarks
   * Write remarks for ~Texture here.
   *
   * \see
   * Separate items with the '|' character.
   */
  ~Texture();
  /*!
   * \brief
   * Write brief comment for Filename here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for Filename here.
   *
   * \remarks
   * Write remarks for Filename here.
   *
   * \see
   * Separate items with the '|' character.
   */
  string Filename();
  /*!
   * \brief
   * Write brief comment for ID here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for ID here.
   *
   * \remarks
   * Write remarks for ID here.
   *
   * \see
   * Separate items with the '|' character.
   */
  uint32_t ID();
  /*!
   * \brief
   * Write brief comment for Load here.
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
   * Write detailed description for Load here.
   *
   * \remarks
   * Write remarks for Load here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool Load(string filename);
  /*!
   * \brief
   * Write brief comment for Load here.
   *
   * \param filename
   * Description of parameter filename.
   *
   * \param min
   * Description of parameter min.
   *
   * \param mag
   * Description of parameter mag.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for Load here.
   *
   * \remarks
   * Write remarks for Load here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool Load(string filename, uint32_t min, uint32_t mag);
  /*!
   * \brief
   * Write brief comment for Free here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for Free here.
   *
   * \remarks
   * Write remarks for Free here.
   *
   * \see
   * Separate items with the '|' character.
   */
  void Free();
  /*!
   * \brief
   * Write brief comment for Loaded here.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for Loaded here.
   *
   * \remarks
   * Write remarks for Loaded here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool Loaded();
  /*!
   * \brief
   * Write brief comment for operator < here.
   *
   * \param
   * Description of parameter .
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for operator < here.
   *
   * \remarks
   * Write remarks for operator < here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool operator<(const Texture&);
  /*!
   * \brief
   * Write brief comment for operator <= here.
   *
   * \param
   * Description of parameter .
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for operator <= here.
   *
   * \remarks
   * Write remarks for operator <= here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool operator<=(const Texture&);
  /*!
   * \brief
   * Write brief comment for operator == here.
   *
   * \param
   * Description of parameter .
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for operator == here.
   *
   * \remarks
   * Write remarks for operator == here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool operator==(const Texture&);
  /*!
   * \brief
   * Write brief comment for operator != here.
   *
   * \param
   * Description of parameter .
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for operator != here.
   *
   * \remarks
   * Write remarks for operator != here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool operator!=(const Texture&);
  /*!
   * \brief
   * Write brief comment for operator >= here.
   *
   * \param
   * Description of parameter .
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for operator >= here.
   *
   * \remarks
   * Write remarks for operator >= here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool operator>=(const Texture&);
  /*!
   * \brief
   * Write brief comment for operator > here.
   *
   * \param
   * Description of parameter .
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for operator > here.
   *
   * \remarks
   * Write remarks for operator > here.
   *
   * \see
   * Separate items with the '|' character.
   */
  bool operator>(const Texture&);

 private:
  uint32_t minFilter;
  uint32_t magFilter;
  std::string filename;
  uint32_t id;
};
}  // End namespace OpenArena
#endif  // End !defined(OpenArena__myglTexture_h__)
