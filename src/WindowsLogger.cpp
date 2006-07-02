#include <cstdlib>
#include "WindowsLogger.h"
#include <windows.h>
namespace OpenArena
{
	WindowsLogger::WindowsLogger()
	{
		_type = MESSAGETYPE_ALL;
	}

	WindowsLogger::~WindowsLogger(void)
	{
	}

	WindowsLogger::WindowsLogger(Logger::MessageType type)
	{
		_type = type;
	}

	void WindowsLogger::Log(const char* message, MessageType type)
	{
		Log(message, "unspecified", type);
	}

	void WindowsLogger::Log(const char* message, const char* classification, MessageType type)
	{
		if(_type != MESSAGETYPE_NONE || _type == type || _type == MESSAGETYPE_ALL)
		{
			MessageBox(NULL, message, classification, MB_OK | GetIconFromMessageType(type));
		}
	}

	uint32 WindowsLogger::GetIconFromMessageType(MessageType type)
	{
		switch (type)
		{
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
};