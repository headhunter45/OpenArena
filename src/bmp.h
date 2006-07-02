#ifndef __bmp_h__
#define __bmp_h__

#include "Image.h"
#include "mygl.h"
#include "datatypes.h"
#include "texture.h"

namespace OpenArena{

	/*!
	  * \brief
	  * BitmapImage implements the Image interface and is used to load *.bmp files.
	  * 
	  * BitmapImage implements the Image interface which replaces the soon-to-be-removed TextureImage class.  When complete the texture class will accept an Image as the image to generate the texture from.
	  * 
	  * \remarks
	  * I would like to make GetImageData return a const uint8 * but I'm not yet sure this will be possible.  To create an editable image use the BufferedImage class which as yet hasn't been implemented.  A created BitmapImage is expected to not change once it's created.  Doing so may break functionality or cause a crash.
	  * 
	  * \see
	  * Image
	  */
	class BitmapImage: public Image
	{
	public:
		virtual ~BitmapImage();
		virtual uint8 * GetImageData() const;
		virtual uint32 GetBitsPerPixel() const;
		virtual uint32 GetBytesPerPixel() const;
		virtual uint32 GetWidth() const;
		virtual uint32 GetHeight() const;
		virtual Image::Type GetType() const;
		static BitmapImage* CreateFromFile(const char* filename);
		static TextureImage* LoadBMP(const char* Filename);
	private:
		BitmapImage();
		BitmapImage(uint32 width, uint32 height, uint32 = 24, Image::Type = Image::Type_RGB);
		uint8* _data;
		uint32 _width;
		uint32 _height;
		uint32 _bpp;
		Image::Type _type;
	public:
#pragma pack(push,1)
		struct BITMAP_HEADER
		{
			uint16 type;
			uint32 size;
			uint16 reserved1;
			uint16 reserved2;
			uint32 offset;
		};

		struct BITMAP_INFO
		{
			uint32 size;
			uint32 width;
			uint32 height;
			uint16 planes;
			uint16 bitCount;
			uint32 compression;
			uint32 sizeImage;
			uint32 xPelsPerMeter;
			uint32 yPelsPerMeter;
			uint32 clrUsed;
			uint32 clrImportant;
		};

		struct BITMAP_QUAD
		{
			uint8 blue;
			uint8 green;
			uint8 red;
			uint8 reserved;
		};
#pragma pack(pop)

#define BITMAP_MAGIC 19778
	};
};

#endif
