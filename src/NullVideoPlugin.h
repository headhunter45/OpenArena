#pragma once
#include "VideoPlugin.h"

namespace OpenArena
{

	/*!
	 * \brief
	 * Write brief comment for NullVideoPlugin here.
	 * 
	 * Write detailed description for NullVideoPlugin here.
	 * 
	 * \remarks
	 * Write remarks for NullVideoPlugin here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class NullVideoPlugin :
		public OpenArena::VideoPlugin
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for NullVideoPlugin here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for NullVideoPlugin here.
		 * 
		 * \remarks
		 * Write remarks for NullVideoPlugin here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		NullVideoPlugin(void);
	public:
		/*!
		 * \brief
		 * Write brief comment for ~NullVideoPlugin here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~NullVideoPlugin here.
		 * 
		 * \remarks
		 * Write remarks for ~NullVideoPlugin here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual ~NullVideoPlugin(void);
		/*!
		 * \brief
		 * Write brief comment for CreateNewWindow here.
		 * 
		 * \param width
		 * Description of parameter width.
		 * 
		 * \param height
		 * Description of parameter height.
		 * 
		 * \param bpp
		 * Description of parameter bpp.
		 * 
		 * \param fullscreen
		 * Description of parameter fullscreen.
		 * 
		 * \param title
		 * Description of parameter title.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for CreateNewWindow here.
		 * 
		 * \remarks
		 * Write remarks for CreateNewWindow here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual Window* CreateNewWindow(uint32 width, uint32 height, uint32 bpp = 32, bool fullscreen = false, const char* title = NULL);
	};

};
