#ifndef __image_h__
#define __image_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "datatypes.h"

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Image here.
	 * 
	 * Write detailed description for Image here.
	 * 
	 * \remarks
	 * Write remarks for Image here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Image
	{
	public:
		//RGB should equal GL_RGB;
		enum Type{Type_RGB};
		/*!
		 * \brief
		 * Write brief comment for GetImageData here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetImageData here.
		 * 
		 * \remarks
		 * Write remarks for GetImageData here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual uint8 * GetImageData() const = 0;
		/*!
		 * \brief
		 * Write brief comment for GetBitsPerPixel here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetBitsPerPixel here.
		 * 
		 * \remarks
		 * Write remarks for GetBitsPerPixel here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual uint32 GetBitsPerPixel() const = 0;
		/*!
		 * \brief
		 * Write brief comment for GetBytesPerPixel here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetBytesPerPixel here.
		 * 
		 * \remarks
		 * Write remarks for GetBytesPerPixel here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual uint32 GetBytesPerPixel() const = 0;
		/*!
		 * \brief
		 * Write brief comment for GetWidth here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetWidth here.
		 * 
		 * \remarks
		 * Write remarks for GetWidth here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual uint32 GetWidth() const = 0;
		/*!
		 * \brief
		 * Write brief comment for GetHeight here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetHeight here.
		 * 
		 * \remarks
		 * Write remarks for GetHeight here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual uint32 GetHeight() const = 0;
		/*!
		 * \brief
		 * Write brief comment for GetType here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetType here.
		 * 
		 * \remarks
		 * Write remarks for GetType here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual Image::Type GetType() const = 0;
		/*!
		 * \brief
		 * Write brief comment for ~Image here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~Image here.
		 * 
		 * \remarks
		 * Write remarks for ~Image here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		virtual ~Image(void){}
	};
};

#endif
