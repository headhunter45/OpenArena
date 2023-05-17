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
#include "console_logger.h"
#include <iostream>
#include <string>

// clang-format on

namespace OpenArena {
namespace {
using std::cout;
using std::endl;
using std::string;
}  // End namespace

ConsoleLogger::ConsoleLogger() {}

ConsoleLogger::~ConsoleLogger() {}

void ConsoleLogger::LogMessage(const MessageType& type, const std::string& message) const {
  cout << "[" << GetTitle(type) << "] " << message << endl;
}

void ConsoleLogger::LogError(const MessageType& type, const std::exception& ex) const {
  cout << "[" << GetTitle(type) << "] caught exception: " << ex.what() << endl;
}

void ConsoleLogger::LogError(const MessageType& type, const std::string& message, const std::exception& ex) const {
  cout << "[" << GetTitle(type) << "] " << message << " with caught exception " << ex.what() << endl;
}

string ConsoleLogger::GetTitle(const MessageType& type) const {
  switch (type) {
    case Debug:
      return "Debug";
    case Error:
      return "Error";
    case Wtf:
      return "Wtf";
    case Info:
      return "Info";
    case Warning:
      return "Warning";
    case Verbose:
      return "Verbose";
    default:
      return "Unclassified";
  }
}

}  // End namespace OpenArena
