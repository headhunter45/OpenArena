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

// Documentation for the windows api stuff used here is available at
// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
// clang-format off
#include "WindowsLogger.h"
#ifdef _WIN32
#include <windows.h>
#include <winuser.h>

#include <cstdlib>
#include <exception>
#include <string>
#endif
// clang-format on
namespace OpenArena {
#ifdef _WIN32
namespace {
using std::exception;
using std::string;
const string kDebugMessageTitle = "Debug";
const string kErrorMessageTitle = "ERROR";
const string kInfoMessageTitle = "Information";
const string kVerboseMessageTitle = "Verbose";
const string kWarningMessageTitle = "Warning";
const string kWtfMessageTitle = "How did you let this happen?";
const string kUnknownMessageTitle = "Unknown";
}  // End namespace

WindowsLogger::WindowsLogger() {}

WindowsLogger::~WindowsLogger() {}

void WindowsLogger::LogMessage(const MessageType& type, const string& message) const {
  MessageBox(NULL, message.c_str(), GetTitle(type).c_str(), MB_OK | GetIcon(type));
}

void WindowsLogger::LogError(const MessageType& type, const exception& ex) const {
  Logger::LogToDo("Implement OpenArena::WindowsLogger::LogError(MessageType, exception)");
}

void WindowsLogger::LogError(const MessageType& type, const std::string& message, const std::exception& ex) const {
  Logger::LogToDo("Implement OpenArena::WindowsLogger::LogError(MessageType, exception, message)");
}

/*
MB_ICONEXCLAMATION - An exclamation point.
MB_ICONWARNING     - An exclamation point. Alias for MB_ICONEXCLAMATION.
MB_ICONINFORMATION - A lowercase i.
MB_ICONASTERISK    - A lowercase i. Alias for MB_ICONINFORMATION.
MB_ICONQUESTION    - A question mark. Don't use this, because it's confusing to users.
MB_ICONSTOP        - A stop sign icon.
MB_ICONERROR       - A stop sign icon. Alias for MB_ICONSTOP.
MB_ICONHAND        - A stop sign icon. Alias for MB_ICONSTOP.
*/
uint32_t WindowsLogger::GetIcon(const MessageType& type) const {
  switch (type) {
    case MessageType::Debug:
      return MB_ICONEXCLAMATION;
    case MessageType::Error:
      return MB_ICONSTOP;
    case MessageType::Info:
      return MB_ICONINFORMATION;
    case MessageType::Verbose:
      return MB_ICONINFORMATION;
    case MessageType::Warning:
      return MB_ICONEXCLAMATION;
    case MessageType::Wtf:
      return MB_ICONSTOP;
    default:
      return MB_ICONINFORMATION;
  }
}

string WindowsLogger::GetTitle(const MessageType& type) const {
  switch (type) {
    case MessageType::Debug:
      return kDebugMessageTitle;
    case MessageType::Error:
      return kErrorMessageTitle;
    case MessageType::Info:
      return kInfoMessageTitle;
    case MessageType::Verbose:
      return kVerboseMessageTitle;
    case MessageType::Warning:
      return kWarningMessageTitle;
    case MessageType::Wtf:
      return kWtfMessageTitle;
    default:
      return kUnknownMessageTitle;
  }
}
#endif
}  // End namespace OpenArena

#ifdef WIN32
namespace OpenArena {};  // namespace OpenArena
#endif
