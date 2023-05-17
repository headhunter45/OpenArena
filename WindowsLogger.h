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
// clang-format off
#include <cstdint>
#include <exception>
#include <string>
#include "logger.h"

// clang-format on

namespace OpenArena {
class WindowsLogger : public OpenArena::Logger {
 private:
  uint32_t GetIcon(const MessageType& type) const;
  std::string GetTitle(const MessageType& type) const;

 public:
  WindowsLogger();
  virtual ~WindowsLogger();
  virtual void LogMessage(const MessageType& type, const std::string& message) const;
  virtual void LogError(const MessageType& type, const std::exception& ex) const;
  virtual void LogError(const MessageType& type, const std::string& message, const std::exception& ex) const;
};
}  // namespace OpenArena

#endif  // End !defined(OpenArena__WindowsLogger_h__)
