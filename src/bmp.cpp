////////////////////////////////////////////////////////////////////////////////
//
//	Module:		bmp.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	10-09-2003
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

#include "../include/bmp.h"

TextureImage* LoadBMP(const char* fn)
{
	//If anything is not perfect return NULL after cleaning up our mess

	FILE* f=NULL;	//A pointer to our file structure

	//If our filename is null
	if(!fn)
		return NULL;


	//Try to open our file and if successfull...
	f=fopen(fn, "r");
	if(f)
	{
		//close the file 
		fclose(f);

		//Load our bitmap structure from the file.
		AUX_RGBImageRec* bmp = auxDIBImageLoad(fn);

		//If the load was successfull.
		if(bmp)
		{
			//Allocate memory for a TextureImage Structure.
			TextureImage* tex = new TextureImage;
			
			 //Convert the bitmap to a TextureImage.
			tex->data = bmp->data;
			tex->sizeX = bmp->sizeX;
			tex->sizeY = bmp->sizeY;
			tex->type = GL_RGB;
			tex->bpp = 3;
			
			//Free the bitmap but not it's data and return our TextureImage.
			free(bmp);
			return tex;
		}
	}
	return NULL;
}
