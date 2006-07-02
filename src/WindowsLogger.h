#pragma once
#include "logger.h"
#include "datatypes.h"

namespace OpenArena
{
	class WindowsLogger :
		public OpenArena::Logger
	{
	private:
		uint32 GetIconFromMessageType(MessageType type);
		MessageType _type;
	public:
		WindowsLogger();
		WindowsLogger(Logger::MessageType type);
		virtual void Log(const char* message, MessageType type=MESSAGETYPE_INFORMATION);
		virtual void Log(const char* message, const char* classification, MessageType type=MESSAGETYPE_INFORMATION);
		virtual ~WindowsLogger();
	};
};