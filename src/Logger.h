#pragma once

namespace OpenArena
{
	class Logger
	{
	public:
		enum MessageType{MESSAGETYPE_ALL, MESSAGETYPE_NONE, MESSAGETYPE_INFORMATION, MESSAGETYPE_ERROR, MESSAGETYPE_DEBUG};
		virtual ~Logger(void){}
		virtual void Log(const char* message, MessageType type=MESSAGETYPE_INFORMATION) = 0;
		virtual void Log(const char* message, const char* classification, MessageType type=MESSAGETYPE_INFORMATION) = 0;
	};
};
