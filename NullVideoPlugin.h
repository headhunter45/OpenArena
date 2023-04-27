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
#ifndef OpenArena__NullVideoPlugin_h__
#define OpenArena__NullVideoPlugin_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "VideoPlugin.h"

namespace OpenArena {

/*!
 * \brief
 * Write brief comment for NullVideoPlugin here.
 *
 * Write detailed description for NullVideoPlugin here.
 *
 * \remarks
 * Write remarks for NullVideoPlugin here.
 *
 * \see
 * Separate items with the '|' character.
 */
class NullVideoPlugin : public OpenArena::VideoPlugin {
 public:
  /*!
   * \brief
   * Write brief comment for NullVideoPlugin here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for NullVideoPlugin here.
   *
   * \remarks
   * Write remarks for NullVideoPlugin here.
   *
   * \see
   * Separate items with the '|' character.
   */
  NullVideoPlugin(void);

 public:
  /*!
   * \brief
   * Write brief comment for ~NullVideoPlugin here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for ~NullVideoPlugin here.
   *
   * \remarks
   * Write remarks for ~NullVideoPlugin here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual ~NullVideoPlugin(void);
  /*!
   * \brief
   * Write brief comment for CreateNewWindow here.
   *
   * \param width
   * Description of parameter width.
   *
   * \param height
   * Description of parameter height.
   *
   * \param bpp
   * Description of parameter bpp.
   *
   * \param fullscreen
   * Description of parameter fullscreen.
   *
   * \param title
   * Description of parameter title.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for CreateNewWindow here.
   *
   * \remarks
   * Write remarks for CreateNewWindow here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual Window* CreateNewWindow(
      uint32_t width, uint32_t height, uint32_t bpp = 32, bool fullscreen = false, const char* title = NULL);
};

}  // End namespace OpenArena

#endif  // End !defined(OpenArena__NullVideoPlugin_h__)
