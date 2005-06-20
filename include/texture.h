#ifndef __texture_h__
#define __texture_h__

struct TextureImage
{
	unsigned char* data;
	unsigned int bpp;
	unsigned int sizeX;
	unsigned int sizeY;
	unsigned int type;
};

#endif
