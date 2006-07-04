#ifndef __bmp_h__
#define __bmp_h__

#include "texture.h"

namespace OpenArena{
	/*!
	 * \brief
	 * Loads a bitmap (*.bmp) file and returns a pointer to a TextureImage object.
	 * 
	 * \param filename
	 * The path to the file to open.
	 * 
	 * \returns
	 * A pointer to the created TextureImage object.
	 * 
	 * \remarks
	 * Will be replaced with an actual class soon
	 * 
	 * \see
	 */
	TextureImage* LoadBMP(const char* Filename);
};

#endif
