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
#include "Logger.h"
#include <algorithm>
#include <exception>
#include <memory>
#include <string>
#include <vector>

// clang-format on

namespace OpenArena {
namespace {
using std::exception;
using std::shared_ptr;
using std::string;
using std::vector;
vector<shared_ptr<Logger>> loggers_;
}  // namespace

// This should log a debug messge that the calling method is not implemented.
#if __cplusplus >= 202002L
void Logger::LogUnimplementedMethod(std::source_location location) {
  ostringstream error_message;
  error_message << "Unimplemented method: \"" << location.function_name() << "\" at " << location.file_name() << " ("
                << location.line() << ":" << location.column() << ")";
  LogDebug(error_message.str());
}
#elif defined __GNUC__

#else
void Logger::LogUnimplementedMethodReal(string method_name) {
  LogDebug("Unimplemented method: " + method_name);
}
#endif

void Logger::LogUnhandledError(const exception& ex) {
  LogDebug("Unhandled Exception", ex);
}

void Logger::LogUnimplementedFeature(const string& feature) {
  LogDebug("Unimplemented feature: " + feature);
}

void Logger::LogWtf(const string& message) {
  Log(Wtf, message);
}

void Logger::LogWtf(const exception& ex) {
  Log(Wtf, ex);
}

void Logger::LogWtf(const string& message, const exception& ex) {
  Log(Wtf, message, ex);
}

void Logger::LogError(const string& message) {
  Log(Error, message);
}

void Logger::LogError(const exception& ex) {
  Log(Error, ex);
}

void Logger::LogError(const string& message, const exception& ex) {
  Log(Error, message, ex);
}

void Logger::LogWarning(const string& message) {
  Log(Warning, message);
}

void Logger::LogWarning(const exception& ex) {
  Log(Warning, ex);
}

void Logger::LogWarning(const string& message, const exception& ex) {
  Log(Warning, message, ex);
}

void Logger::LogInfo(const string& message) {
  Log(Info, message);
}

void Logger::LogInfo(const exception& ex) {
  Log(Info, ex);
}

void Logger::LogInfo(const string& message, const exception& ex) {
  Log(Info, message, ex);
}

void Logger::LogDebug(const string& message) {
  Log(Debug, message);
}

void Logger::LogDebug(const exception& ex) {
  Log(Debug, ex);
}

void Logger::LogDebug(const string& message, const exception& ex) {
  Log(Debug, message, ex);
}

void Logger::LogVerbose(const string& message) {
  Log(Verbose, message);
}

void Logger::LogVerbose(const exception& ex) {
  Log(Verbose, ex);
}

void Logger::LogVerbose(const string& message, const exception& ex) {
  Log(Verbose, message, ex);
}

void Logger::Log(const MessageType& type, const string& message) {
  for (const auto& logger : loggers_) {
    if (type >= logger->GetMinType() && type <= logger->GetMaxType()) {
      logger->LogMessage(type, message);
    }
  }
}

void Logger::Log(const MessageType& type, const exception& ex) {
  for (const auto& logger : loggers_) {
    if (type >= logger->GetMinType() && type <= logger->GetMaxType()) {
      logger->LogError(type, ex);
    }
  }
}

void Logger::Log(const MessageType& type, const string& message, const exception& ex) {
  for (const auto& logger : loggers_) {
    if (type >= logger->GetMinType() && type <= logger->GetMaxType()) {
      logger->LogError(type, message, ex);
    }
  }
}

void Logger::Reset() {
  loggers_.clear();
}

void Logger::AddLogger(shared_ptr<Logger> logger) {
  loggers_.push_back(logger);
}

void Logger::LogToDo(const string& message) {
  LogDebug(" // TODO: " + message);
}

Logger::Logger() : min_type_(MessageType::Unknown), max_type_(MessageType::Wtf) {}

Logger::~Logger() {}

void Logger::SetMinType(const MessageType& type) {
  min_type_ = type;
}

void Logger::SetMaxType(const MessageType& type) {
  max_type_ = type;
}

Logger::MessageType Logger::GetMinType() const {
  return min_type_;
}

Logger::MessageType Logger::GetMaxType() const {
  return max_type_;
}
}  // End namespace OpenArena
