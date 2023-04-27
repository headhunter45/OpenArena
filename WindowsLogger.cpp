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
#ifdef WIN32
#include "WindowsLogger.h"

#include <windows.h>

#include <cstdlib>

namespace OpenArena {
WindowsLogger::WindowsLogger() {
  _type = MESSAGETYPE_ALL;
}

WindowsLogger::~WindowsLogger(void) {}

WindowsLogger::WindowsLogger(Logger::MessageType type) {
  _type = type;
}

void WindowsLogger::Log(const char* message, MessageType type) {
  Log(message, "unspecified", type);
}

void WindowsLogger::Log(const char* message, const char* classification, MessageType type) {
  if (_type != MESSAGETYPE_NONE || _type == type || _type == MESSAGETYPE_ALL) {
    MessageBox(NULL, message, classification, MB_OK | GetIconFromMessageType(type));
  }
}

uint32 WindowsLogger::GetIconFromMessageType(MessageType type) {
  switch (type) {
    case MESSAGETYPE_ERROR:
      return MB_ICONERROR;
    case MESSAGETYPE_INFORMATION:
      return MB_ICONINFORMATION;
    case MESSAGETYPE_DEBUG:
      return MB_ICONWARNING;
    default:
      return MB_ICONASTERISK;
  };
}
};  // namespace OpenArena
#endif
