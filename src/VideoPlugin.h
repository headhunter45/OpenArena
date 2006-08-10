#ifndef __VideoPlugin_h__
#define __VideoPlugin_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "Plugin.h"
#include "window.h"
#include "datatypes.h"

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for VideoPlugin here.
	 * 
	 * Write detailed description for VideoPlugin here.
	 * 
	 * \remarks
	 * Write remarks for VideoPlugin here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class VideoPlugin :public Plugin
	{
	public:
	public:
		/*!
		 * \brief
		 * Write brief comment for ~VideoPlugin here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~VideoPlugin here.
		 * 
		 * \remarks
		 * Write remarks for ~VideoPlugin here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual ~VideoPlugin(){}
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
		virtual Window* CreateNewWindow(uint32 width,
			uint32 height, 
			uint32 bpp = 32, 
			bool fullscreen = false, 
			const char* title = NULL) = 0;
	};
};

#endif
