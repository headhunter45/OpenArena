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
#include "../include/bmp.h"

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
		BITMAP_HEADER bmpHeader;
		BITMAP_INFO bmpInfo;
		BITMAP_QUAD* bmpPallette = NULL;
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
			bmpPallette = new BITMAP_QUAD[palletteEntries];
			fread(bmpPallette, sizeof(BITMAP_QUAD), palletteEntries, f);
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
				i2 = i << 1 + 1;
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
