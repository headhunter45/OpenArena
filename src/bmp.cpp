////////////////////////////////////////////////////////////////////////////////
//
//	Module:		bmp.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	06-20-2005
//	Editors:	Tom Hicks
//
//	Purpose:
//		To implement a wrapper function that will load a 24bit windows bitmap
//	file and return a pointer to a TextureImage object containing the image.
//
//	Summary of Methods:
//	Global
//		-LoadBMP
//			Loads a 24 bit windows bitmap file specified by fn and returns a
//				pointer to a TextureImage object containing the bitmap image.
//
////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include "bmp.h"
#ifdef WIN32
#pragma warning(disable:4996)
#endif

namespace OpenArena{

	BitmapImage::BitmapImage()
	{
		BitmapImage(1, 1);
	}

	
	BitmapImage::BitmapImage(uint32 width, uint32 height, uint32 bitsPerPixel, Image::Type type)
	{
		_width = width;
		_height = height;
		_bpp = bitsPerPixel;
		_type = type;
		_data = new uint8[_width * _height * (_bpp >> 3)];
	}

	BitmapImage::~BitmapImage()
	{
		delete [] _data;
	}

	uint8 * BitmapImage::GetImageData() const
	{
		return _data;
	}

	uint32 BitmapImage::GetBitsPerPixel() const
	{
		return _bpp;
	}

	uint32 BitmapImage::GetBytesPerPixel() const
	{
		return _bpp >> 3;
	}
	
	uint32 BitmapImage::GetWidth() const
	{
		return _width;
	}

	uint32 BitmapImage::GetHeight() const
	{
		return _height;
	}

	Image::Type BitmapImage::GetType() const
	{
		return _type;
	}

	BitmapImage* BitmapImage::CreateFromFile(const char* filename)
	{
		FILE* file = NULL;	//A file from cstdlib?

		//If our filename is null return an empty 1x1 image
		if(filename == NULL)
		{
			return new BitmapImage(1,1);
		}

		//Try to open the file
		file = fopen(filename, "rb");

		//If the open failed return an empry 1x1 image
		if(file == NULL)
		{
			return new BitmapImage(1,1);
		}

		BITMAP_HEADER bmpHeader;
		BITMAP_INFO bmpInfo;
		BITMAP_QUAD* pallette = NULL;
		uint32 numPalletteEntries = 0;
		uint32 numPixels;

		//Read the header from the file
		fread(&bmpHeader, sizeof(bmpHeader), 1, file);
		fread(&bmpInfo, sizeof(bmpInfo), 1, file);

		//Check for an invalid header
		if(bmpInfo.width < 0)	//See if the width is negative
		{
			//This needs to be abstracted somehow
#ifdef WIN32
			MessageBox(NULL, "Image width is negative", "ERROR", MB_OK);
#endif
			fclose(file);
			return NULL;
		}
		if(bmpInfo.width % 4 != 0) //If the width is not a multiple of 4
		{
			//This needs to be abstracted somehow
#ifdef WIN32
			MessageBox(NULL, "Image width must be a multiple of 8", "ERROR", MB_OK);
#endif
			fclose(file);
			return NULL;
		}

		if(bmpInfo.height < 0) //If the height is negative
		{
			//This needs to be abstracted somehow
#ifdef WIN32
			MessageBox(NULL, "Image height is negative", "ERROR", MB_OK);
#endif
			fclose(file);
			return NULL;
		}
		if(bmpInfo.height % 4 != 0)	//If the height is not a multiple of 4
		{
			//This needs to be abstracted somehow
#ifdef WIN32
			MessageBox(NULL, "Image height must be a multiple of 8", "ERROR", MB_OK);
#endif
			fclose(file);
			return NULL;
		}

		if((bmpInfo.bitCount != 8 && bmpInfo.bitCount != 24) || bmpInfo.compression != 0)  //Make sure the file is 8 or 24 bit and uncompressed
		{			//This needs to be abstracted somehow
#ifdef WIN32
			MessageBox(NULL, "Only 8 and 24 bit uncompressed windows bmp files are currently supported", "ERROR", MB_OK);
#endif
			fclose(file);
			return NULL;
		}

		BitmapImage* image = new BitmapImage(bmpInfo.width, bmpInfo.height, bmpInfo.bitCount, (Type)GL_RGB);

		numPixels = image->GetWidth() * image->GetHeight();

		//If 8-bit load the pallette
		if(image->GetBitsPerPixel() == 8)
		{
			//TODO finish this
			numPalletteEntries = image->GetBytesPerPixel();
			pallette = new BITMAP_QUAD[numPalletteEntries];
//			fread(pallette, sizeof(OpenArena::Bitmap::BITMAP_QUAD), pallette, file);
		}

		//Seek to the start of data
		fseek(file, bmpHeader.offset, SEEK_SET);
		
		//Read the image data
		fread(image->_data, numPixels * image->GetBytesPerPixel(), 1, file);

		//If 8-bit apply the pallette
		if(image->GetBitsPerPixel() == 8)
		{
			//TODO finish this
			uint32 i1, i2;
			for(i1=0; i1<numPixels; i1++)
			{
				i2 = (i1 << 1) + 1;
				if(image->_data[i1] < numPalletteEntries)
				{
					image->_data[i2] = pallette[image->_data[i1]].red;
					image->_data[i2+1] = pallette[image->_data[i1]].blue;
					image->_data[i2+2] = pallette[image->_data[i1]].green;
				}
			}
			//uint8* image = tex->data;
			//tex->bpp = 24;
			//bytes = pixels * tex->bpp;
			//tex->data = new uint8[bytes];

			//uint32 i;
			//uint32 i2;
			//for(i=0; i<pixels; i++)
			//{
			//	i2 = (i << 1) + 1;
			//	//Should make sure image[i] < palletteEntries
			//	tex->data[i2] = bmpPallette[image[i]].red;
			//	tex->data[i2 + 1] = bmpPallette[image[i]].blue;
			//	tex->data[i2 + 2] = bmpPallette[image[i]].green;
			//}
			//delete [] image;
			//image = NULL;
		}
		else if(image->GetBitsPerPixel() == 24)
		{
			//Convert to rgb
			uint32 i;
			uint8 swap;

			for(i=0; i<numPixels * image->GetBytesPerPixel(); i+=3)
			{
				swap = image->_data[i];
				image->_data[i] = image->_data[i+2];
				image->_data[i+2] = swap;
			}
		}

		return image;
	}

	TextureImage* LoadBMP(const char* fn)
	{
		//If anything is not perfect return NULL after cleaning up our mess

		FILE* f=NULL;	//A pointer to our file structure

		//If our filename is null
		if(!fn)
			return NULL;

		//Try to open our file and if successfull...

		f=fopen(fn, "rb");
		if(f)
		{
			BitmapImage::BITMAP_HEADER bmpHeader;
			BitmapImage::BITMAP_INFO bmpInfo;
			BitmapImage::BITMAP_QUAD* bmpPallette = NULL;
			uint32 palletteEntries = 0;

			fread(&bmpHeader, sizeof(bmpHeader), 1, f);
			fread(&bmpInfo, sizeof(bmpInfo), 1, f);

			if(bmpInfo.width < 0)
			{
				//This needs to be abstracted somehow
#ifdef WIN32
				MessageBox(NULL, "Image width is negative", "ERROR", MB_OK);
#endif
				fclose(f);
				return NULL;
			}

			if(bmpInfo.width % 4 != 0)
			{
				//This needs to be abstracted somehow
#ifdef WIN32
				MessageBox(NULL, "Image width must be a multiple of 8", "ERROR", MB_OK);
#endif
				fclose(f);
				return NULL;
			}

			if(bmpInfo.height < 0)
			{
				//This needs to be abstracted somehow
#ifdef WIN32
				MessageBox(NULL, "Image height is negative", "ERROR", MB_OK);
#endif
				fclose(f);
				return NULL;
			}

			if(bmpInfo.height % 4 != 0)
			{
				//This needs to be abstracted somehow
#ifdef WIN32
				MessageBox(NULL, "Image height must be a multiple of 8", "ERROR", MB_OK);
#endif
				fclose(f);
				return NULL;
			}

			if((bmpInfo.bitCount != 8 && bmpInfo.bitCount != 24) || bmpInfo.compression != 0)
			{
				//This needs to be abstracted somehow
#ifdef WIN32
				MessageBox(NULL, "Only 8 and 24 bit uncompressed windows bmp files are currently supported", "ERROR", MB_OK);
#endif
				fclose(f);
				return NULL;
			}

			//Allocate memory for a TextureImage structure
			TextureImage* tex = new TextureImage;
			tex->sizeX = bmpInfo.width;
			tex->sizeY = bmpInfo.height;
			if(bmpInfo.bitCount >= 8)
			{
				tex->bpp = bmpInfo.bitCount >> 3;
			}
			tex->type = GL_RGB;
			uint32 pixels = tex->sizeX * tex->sizeY;
			uint32 bytes = pixels * tex->bpp;
			tex->data = new uint8[bytes];

			if(bmpInfo.bitCount == 8)
			{
				//Load the pallette
				palletteEntries = bmpInfo.bitCount << 8;
				bmpPallette = new BitmapImage::BITMAP_QUAD[palletteEntries];
				fread(bmpPallette, sizeof(BitmapImage::BITMAP_QUAD), palletteEntries, f);
			}

			fseek(f, bmpHeader.offset, SEEK_SET);
			fread(tex->data, bytes, 1, f);

			if(bmpInfo.bitCount == 8)
			{
				//Apply the pallette
				uint8* image = tex->data;
				tex->bpp = 24;
				bytes = pixels * tex->bpp;
				tex->data = new uint8[bytes];

				uint32 i;
				uint32 i2;
				for(i=0; i<pixels; i++)
				{
					i2 = (i << 1) + 1;
					//Should make sure image[i] < palletteEntries
					tex->data[i2] = bmpPallette[image[i]].red;
					tex->data[i2 + 1] = bmpPallette[image[i]].blue;
					tex->data[i2 + 2] = bmpPallette[image[i]].green;
				}

				delete [] image;
				image = NULL;
			}
			else if(bmpInfo.bitCount == 24)
			{
				uint32 i;
				uint8 t;

				for(i=0; i<bytes; i+=3)
				{
					t = tex->data[i];
					tex->data[i] = tex->data[i+2];
					tex->data[i+2] = t;
				}
			}
			return tex;
		}
		return NULL;
	}
};