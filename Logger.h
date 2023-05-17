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

#ifndef OpenArena__Logger_h__
#define OpenArena__Logger_h__
// clang-format off
#include <exception>
#include <memory>
#include <string>

// clang-format on

namespace OpenArena {
class Logger {
 public:
  enum MessageType { Unknown = 0, Debug, Verbose, Info, Warning, Error, Wtf };

  Logger();
  virtual ~Logger();

  virtual void LogMessage(const MessageType& type, const std::string& message) const = 0;
  virtual void LogError(const MessageType& type, const std::exception& ex) const = 0;
  virtual void LogError(const MessageType& type, const std::string& message, const std::exception& ex) const = 0;
  virtual void SetMinType(const MessageType& type);
  virtual void SetMaxType(const MessageType& type);
  virtual MessageType GetMinType() const;
  virtual MessageType GetMaxType() const;

// This one is special and annoying because it requires macros until the minimum standard is c++20.
#if __cplusplus >= 202002L
  static void LogUnimplementedMethod(std::source_location = std::source_location::current());
#else
  static void LogUnimplementedMethodReal(std::string method_name);
#endif

  static void LogUnhandledError(const std::exception& ex);
  static void LogUnimplementedFeature(const std::string& feature);
  static void LogWtf(const std::string& message);
  static void LogWtf(const std::exception& ex);
  static void LogWtf(const std::string& message, const std::exception& ex);
  static void LogError(const std::string& message);
  static void LogError(const std::exception& ex);
  static void LogError(const std::string& message, const std::exception& ex);
  static void LogWarning(const std::string& message);
  static void LogWarning(const std::exception& ex);
  static void LogWarning(const std::string& message, const std::exception& ex);
  static void LogInfo(const std::string& message);
  static void LogInfo(const std::exception& ex);
  static void LogInfo(const std::string& message, const std::exception& ex);
  static void LogDebug(const std::string& message);
  static void LogDebug(const std::exception& ex);
  static void LogDebug(const std::string& message, const std::exception& ex);
  static void LogVerbose(const std::string& message);
  static void LogVerbose(const std::exception& ex);
  static void LogVerbose(const std::string& message, const std::exception& ex);
  static void Log(const MessageType& type, const std::string& message);
  static void Log(const MessageType& type, const std::exception& ex);
  static void Log(const MessageType& type, const std::string& message, const std::exception& ex);
  static void LogToDo(const std::string& message);
  static void Reset();
  static void AddLogger(std::shared_ptr<Logger> logger);

 private:
  MessageType min_type_;
  MessageType max_type_;
};

}  // End namespace OpenArena

#if __cplusplus >= 202002L
#elif defined __GNUC__
#define Logger ::LogUnimplementedMethod LogUnimplementedMethodReal(__PRETTY_FUNCTION__);
#else
#define LogUnimplementedMethod Logger::LogUnimplementedMethodReal(__FUNCTION__);
#endif

#endif  // End !defined(OpenArena__Logger_h__)
