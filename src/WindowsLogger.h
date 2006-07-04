#pragma once
#include "logger.h"
#include "datatypes.h"

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for WindowsLogger here.
	 * 
	 * Write detailed description for WindowsLogger here.
	 * 
	 * \remarks
	 * Write remarks for WindowsLogger here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class WindowsLogger :
		public OpenArena::Logger
	{
	private:
		/*!
		 * \brief
		 * Write brief comment for GetIconFromMessageType here.
		 * 
		 * \param type
		 * Description of parameter type.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetIconFromMessageType here.
		 * 
		 * \remarks
		 * Write remarks for GetIconFromMessageType here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		uint32 GetIconFromMessageType(MessageType type);
		MessageType _type;
	public:
		/*!
		 * \brief
		 * Write brief comment for WindowsLogger here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for WindowsLogger here.
		 * 
		 * \remarks
		 * Write remarks for WindowsLogger here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		WindowsLogger();
		/*!
		 * \brief
		 * Write brief comment for WindowsLogger here.
		 * 
		 * \param type
		 * Description of parameter type.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for WindowsLogger here.
		 * 
		 * \remarks
		 * Write remarks for WindowsLogger here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		WindowsLogger(Logger::MessageType type);
		/*!
		 * \brief
		 * Write brief comment for Log here.
		 * 
		 * \param message
		 * Description of parameter message.
		 * 
		 * \param type
		 * Description of parameter type.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Log here.
		 * 
		 * \remarks
		 * Write remarks for Log here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual void Log(const char* message, MessageType type=MESSAGETYPE_INFORMATION);
		/*!
		 * \brief
		 * Write brief comment for Log here.
		 * 
		 * \param message
		 * Description of parameter message.
		 * 
		 * \param classification
		 * Description of parameter classification.
		 * 
		 * \param type
		 * Description of parameter type.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Log here.
		 * 
		 * \remarks
		 * Write remarks for Log here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual void Log(const char* message, const char* classification, MessageType type=MESSAGETYPE_INFORMATION);
		/*!
		 * \brief
		 * Write brief comment for ~WindowsLogger here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~WindowsLogger here.
		 * 
		 * \remarks
		 * Write remarks for ~WindowsLogger here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual ~WindowsLogger();
	};
};