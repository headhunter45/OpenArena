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

#ifndef OpenArena__console_logger_h__
#define OpenArena__console_logger_h__
// clang-format off
#include "Logger.h"

// clang-format on

namespace OpenArena {
class ConsoleLogger : public Logger {
 public:
  ConsoleLogger();
  virtual ~ConsoleLogger();
  virtual void LogMessage(const MessageType& type, const std::string& message) const;
  virtual void LogError(const MessageType& type, const std::exception& ex) const;
  virtual void LogError(const MessageType& type, const std::string& message, const std::exception& ex) const;

 private:
  std::string GetTitle(const MessageType& type) const;
};
}  // namespace OpenArena

#endif  // End !defined(OpenArena__console_logger_h__)
