#pragma once

#include "datatypes.h"

namespace OpenArena
{
	class Image
	{
	public:
		//RGB should equal GL_RGB;
		enum Type{Type_RGB};
		virtual uint8 * GetImageData() const = 0;
		virtual uint32 GetBitsPerPixel() const = 0;
		virtual uint32 GetBytesPerPixel() const = 0;
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		virtual Image::Type GetType() const = 0;
		virtual ~Image(void){}
	};
};

