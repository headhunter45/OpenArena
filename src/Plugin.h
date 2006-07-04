#pragma once

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Plugin here.
	 * 
	 * Write detailed description for Plugin here.
	 * 
	 * \remarks
	 * Write remarks for Plugin here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Plugin
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for ~Plugin here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~Plugin here.
		 * 
		 * \remarks
		 * Write remarks for ~Plugin here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual ~Plugin(void){}
		/*!
		 * \brief
		 * Write brief comment for InputPlugin here.
		 */
		enum Type {VideoPlugin, AudioPlugin, InputPlugin};
	};


};