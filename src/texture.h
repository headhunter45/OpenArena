#ifndef __texture_h__
#define __texture_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for TextureImage here.
	 * 
	 * Write detailed description for TextureImage here.
	 * 
	 * \remarks
	 * Write remarks for TextureImage here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class TextureImage
	{
	public:
		unsigned char* data;
		unsigned int bpp;
		unsigned int sizeX;
		unsigned int sizeY;
		unsigned int type;
	};
};
#endif
