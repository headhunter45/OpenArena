#ifndef __bmp_h__
#define __bmp_h__

#include <gl/glaux.h>
#include <stdio.h>
#include "texture.h"

//AUX_RGBImageRec *LoadBMP(const char *Filename);
TextureImage* LoadBMP(const char* Filename);

#endif
