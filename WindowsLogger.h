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
#ifndef OpenArena__WindowsLogger_h__
#define OpenArena__WindowsLogger_h__
#include <cstdint>
#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "logger.h"

namespace OpenArena {
/*!
 * \brief
 * Write brief comment for WindowsLogger here.
 *
 * Write detailed description for WindowsLogger here.
 *
 * \remarks
 * Write remarks for WindowsLogger here.
 *
 * \see
 * Separate items with the '|' character.
 */
class WindowsLogger : public OpenArena::Logger {
 private:
  /*!
   * \brief
   * Write brief comment for GetIconFromMessageType here.
   *
   * \param type
   * Description of parameter type.
   *
   * \returns
   * Write description of return value here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for GetIconFromMessageType here.
   *
   * \remarks
   * Write remarks for GetIconFromMessageType here.
   *
   * \see
   * Separate items with the '|' character.
   */
  uint32_t GetIconFromMessageType(MessageType type);
  MessageType _type;

 public:
  /*!
   * \brief
   * Write brief comment for WindowsLogger here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for WindowsLogger here.
   *
   * \remarks
   * Write remarks for WindowsLogger here.
   *
   * \see
   * Separate items with the '|' character.
   */
  WindowsLogger();
  /*!
   * \brief
   * Write brief comment for WindowsLogger here.
   *
   * \param type
   * Description of parameter type.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for WindowsLogger here.
   *
   * \remarks
   * Write remarks for WindowsLogger here.
   *
   * \see
   * Separate items with the '|' character.
   */
  WindowsLogger(Logger::MessageType type);
  /*!
   * \brief
   * Write brief comment for Log here.
   *
   * \param message
   * Description of parameter message.
   *
   * \param type
   * Description of parameter type.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for Log here.
   *
   * \remarks
   * Write remarks for Log here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual void Log(const char* message, MessageType type = MESSAGETYPE_INFORMATION);
  /*!
   * \brief
   * Write brief comment for Log here.
   *
   * \param message
   * Description of parameter message.
   *
   * \param classification
   * Description of parameter classification.
   *
   * \param type
   * Description of parameter type.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for Log here.
   *
   * \remarks
   * Write remarks for Log here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual void Log(const char* message, const char* classification, MessageType type = MESSAGETYPE_INFORMATION);
  /*!
   * \brief
   * Write brief comment for ~WindowsLogger here.
   *
   * \throws <exception class>
   * Description of criteria for throwing this exception.
   *
   * Write detailed description for ~WindowsLogger here.
   *
   * \remarks
   * Write remarks for ~WindowsLogger here.
   *
   * \see
   * Separate items with the '|' character.
   */
  virtual ~WindowsLogger();
};
}  // namespace OpenArena

#endif  // End !defined(OpenArena__WindowsLogger_h__)
