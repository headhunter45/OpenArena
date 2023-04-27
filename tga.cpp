/***************************************************************************
 *   Copyright (C) 2001-2023 by Tom Hicks                                  *
 *   headhunter3@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "tga.h"

#include <OpenGL/gl.h>

#ifdef WIN32
#pragma warning(disable : 4996)
#endif

namespace OpenArena {
TextureImage* LoadTGA(const char* filename) {
  TGAHeader tgaheader;
  TextureImage* image;
  std::string errmsg;
  FILE* file = fopen(filename, "rb");

  if (file == NULL) {
    errmsg = "Could not open texture file ";
    errmsg = errmsg + filename;
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, errmsg.c_str(), "ERROR", MB_OK);
#endif
    return NULL;
  }

  if (fread(&tgaheader, sizeof(TGAHeader), 1, file) == 0) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Could not read file header", "ERROR", MB_OK);
#endif
    if (file != NULL) fclose(file);
    return NULL;
  }

  if (memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
    image = LoadUncompressedTGA(file);
  else if (memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
    image = LoadCompressedTGA(file);
  else {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "TGA file must be type 2 or type 10 ", "Invalid Image", MB_OK);
#endif
    fclose(file);
    return NULL;
  }
  return image;
}

TextureImage* LoadUncompressedTGA(FILE* fTGA) {
  TGA tga;
  TextureImage* image = new TextureImage;

  if (fread(tga.header, sizeof(tga.header), 1, fTGA) == 0) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);
#endif
    if (fTGA != NULL) {
      fclose(fTGA);
    }
    return NULL;
  }

  image->sizeY = tga.header[1] * 256 + tga.header[0];
  image->sizeX = tga.header[3] * 256 + tga.header[2];
  image->bpp = tga.header[4];
  tga.Width = image->sizeX;
  tga.Height = image->sizeY;
  tga.Bpp = image->bpp;

  if ((image->sizeX <= 0) || (image->sizeY <= 0) || ((image->bpp != 24) && (image->bpp != 32))) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);
#endif
    if (fTGA != NULL) {
      fclose(fTGA);
    }
    return NULL;
  }

  if (image->bpp == 24) {
    image->type = GL_RGB;
  } else {
    image->type = GL_RGBA;
  }

  tga.bytesPerPixel = (tga.Bpp / 8);
  tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);
  image->data = (uint8_t*)malloc(tga.imageSize);

  if (image->data == NULL) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);
#endif
    fclose(fTGA);
    return NULL;
  }

  if (fread(image->data, 1, tga.imageSize, fTGA) != tga.imageSize) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);
#endif
    if (image->data != NULL) {
      free(image->data);
    }
    fclose(fTGA);
    return NULL;
  }

  for (uint32_t cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel) {
    image->data[cswap] ^= image->data[cswap + 2] ^= image->data[cswap] ^= image->data[cswap + 2];
  }

  fclose(fTGA);
  return image;
}

TextureImage* LoadCompressedTGA(FILE* fTGA) {
  TextureImage* image = new TextureImage;
  TGA tga;

  if (fread(tga.header, sizeof(tga.header), 1, fTGA) == 0) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);
#endif
    if (fTGA != NULL) {
      fclose(fTGA);
    }
    return NULL;
  }

  image->sizeX = tga.header[1] * 256 + tga.header[0];
  image->sizeY = tga.header[3] * 256 + tga.header[2];
  image->bpp = tga.header[4];
  tga.Width = image->sizeX;
  tga.Height = image->sizeY;
  tga.Bpp = image->bpp;

  if ((image->sizeX <= 0) || (image->sizeY <= 0) || ((image->bpp != 24) && (image->bpp != 32))) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);
#endif
    if (fTGA != NULL) {
      fclose(fTGA);
    }
    return NULL;
  }

  tga.bytesPerPixel = (tga.Bpp / 8);
  tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);
  image->data = (uint8_t*)malloc(tga.imageSize);

  if (image->data == NULL) {
// This needs to be abstracted somehow
#ifdef WIN32
    MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);
#endif
    fclose(fTGA);
    return NULL;
  }

  uint32_t pixelcount = tga.Height * tga.Width;
  uint32_t currentpixel = 0;
  uint32_t currentbyte = 0;
  uint8_t* colorbuffer = (uint8_t*)malloc(tga.bytesPerPixel);

  do {
    uint8_t chunkheader = 0;

    if (fread(&chunkheader, sizeof(uint8_t), 1, fTGA) == 0) {
// This needs to be abstracted somehow
#ifdef WIN32
      MessageBox(NULL, "Could not read RLE header", "ERROR", MB_OK);
#endif
      if (fTGA != NULL) {
        fclose(fTGA);
      }
      if (image->data != NULL) {
        free(image->data);
      }
      return NULL;
    }

    if (chunkheader < 128) {
      chunkheader++;
      for (short counter = 0; counter < chunkheader; counter++) {
        if (fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) {
// This needs to be abstracted somehow
#ifdef WIN32
          MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);
#endif

          if (fTGA != NULL) {
            fclose(fTGA);
          }

          if (colorbuffer != NULL) {
            free(colorbuffer);
          }

          if (image->data != NULL) {
            free(image->data);
          }

          return NULL;
        }

        image->data[currentbyte] = colorbuffer[2];
        image->data[currentbyte + 1] = colorbuffer[1];
        image->data[currentbyte + 2] = colorbuffer[0];

        if (tga.bytesPerPixel == 4) {
          image->data[currentbyte + 3] = colorbuffer[3];
        }

        currentbyte += tga.bytesPerPixel;
        currentpixel++;

        if (currentpixel > pixelcount) {
// This needs to be abstracted somehow
#ifdef WIN32
          MessageBox(NULL, "Too many pixels read", "ERROR", NULL);
#endif

          if (fTGA != NULL) {
            fclose(fTGA);
          }

          if (colorbuffer != NULL) {
            free(colorbuffer);
          }

          if (image->data != NULL) {
            free(image->data);
          }

          return NULL;
        }
      }
    } else {
      chunkheader -= 127;
      if (fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) {
// This needs to be abstracted somehow
#ifdef WIN32
        MessageBox(NULL, "Could not read from file", "ERROR", MB_OK);
#endif

        if (fTGA != NULL) {
          fclose(fTGA);
        }

        if (colorbuffer != NULL) {
          free(colorbuffer);
        }

        if (image->data != NULL) {
          free(image->data);
        }

        return NULL;
      }

      for (short counter = 0; counter < chunkheader; counter++) {
        image->data[currentbyte] = colorbuffer[2];
        image->data[currentbyte + 1] = colorbuffer[1];
        image->data[currentbyte + 2] = colorbuffer[0];

        if (tga.bytesPerPixel == 4) {
          image->data[currentbyte + 3] = colorbuffer[3];
        }

        currentbyte += tga.bytesPerPixel;
        currentpixel++;

        if (currentpixel > pixelcount) {
// This needs to be abstracted somehow
#ifdef WIN32
          MessageBox(NULL, "Too many pixels read", "ERROR", NULL);
#endif

          if (fTGA != NULL) {
            fclose(fTGA);
          }

          if (colorbuffer != NULL) {
            free(colorbuffer);
          }

          if (image->data != NULL) {
            free(image->data);
          }

          return NULL;
        }
      }
    }
  }

  while (currentpixel < pixelcount);
  fclose(fTGA);
  return image;
}

/*
TextureImage* LoadTGA(const char * filename)
{
        TGAHeader tgaheader;
        TextureImage* image;
        std::string errmsg;
        FILE* file = fopen(filename, "rb");

        if(file == NULL)
        {
                errmsg = "Could not open texture file ";
                errmsg = errmsg + filename;
                MessageBox(NULL, errmsg.c_str(), "ERROR", MB_OK);
                return NULL;
        }

        if(fread(&tgaheader, sizeof(TGAHeader), 1, file) == 0)
        {
                MessageBox(NULL, "Could not read file header", "ERROR", MB_OK);
                if(file != NULL)
                        fclose(file);
                return NULL;
        }

        if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
                image = LoadUncompressedTGA(file);
        else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
                image = LoadCompressedTGA(file);
        else
        {
                MessageBox(NULL, "TGA file must be type 2 or type 10 ", "Invalid
Image", MB_OK); fclose(file); return NULL;
        }
        return image;
}

TextureImage* LoadUncompressedTGA(FILE * fTGA)
{
        TGA tga;
        TextureImage* image = new TextureImage;

        if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)
        {
                MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);
                if(fTGA != NULL)
                {
                        fclose(fTGA);
                }
                return NULL;
        }

        image->sizeY  = tga.header[1] * 256 + tga.header[0];
        image->sizeX = tga.header[3] * 256 + tga.header[2];
        image->bpp	= tga.header[4];
        tga.Width		= image->sizeX;
        tga.Height		= image->sizeY;
        tga.Bpp			= image->bpp;

        if((image->sizeX <= 0) || (image->sizeY <= 0) || ((image->bpp != 24) &&
(image->bpp !=32)))
        {
                MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);
                if(fTGA != NULL)
                {
                        fclose(fTGA);
                }
                return NULL;
        }

        if(image->bpp == 24)
        {
                image->type	= GL_RGB;
        }
        else
        {
                image->type	= GL_RGBA;
        }

        tga.bytesPerPixel	= (tga.Bpp / 8);
        tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);
        image->data	= (uint8_t *)malloc(tga.imageSize);

        if(image->data == NULL)
        {
                MessageBox(NULL, "Could not allocate memory for image", "ERROR",
MB_OK); fclose(fTGA); return NULL;
        }

        if(fread(image->data, 1, tga.imageSize, fTGA) != tga.imageSize)
        {
                MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);
                if(image->data != NULL)
                {
                        free(image->data);
                }
                fclose(fTGA);
                return NULL;
        }


        for(uint32_t cswap = 0; cswap < (int)tga.imageSize; cswap +=
tga.bytesPerPixel)
        {
                image->data[cswap] ^= image->data[cswap+2] ^=
                image->data[cswap] ^= image->data[cswap+2];
        }

        fclose(fTGA);
        return image;
}

TextureImage* LoadCompressedTGA(FILE * fTGA)
{
        TextureImage* image = new TextureImage;
        TGA tga;

        if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)
        {
                MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);
                if(fTGA != NULL)
                {
                        fclose(fTGA);
                }
                return NULL;
        }

        image->sizeX  = tga.header[1] * 256 + tga.header[0];
        image->sizeY = tga.header[3] * 256 + tga.header[2];
        image->bpp	= tga.header[4];
        tga.Width		= image->sizeX;
        tga.Height		= image->sizeY;
        tga.Bpp			= image->bpp;

        if((image->sizeX <= 0) || (image->sizeY <= 0) || ((image->bpp != 24) &&
(image->bpp !=32)))
        {
                MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);
                if(fTGA != NULL)
                {
                        fclose(fTGA);
                }
                return NULL;
        }

        tga.bytesPerPixel	= (tga.Bpp / 8);
        tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);
        image->data	= (uint8_t *)malloc(tga.imageSize);

        if(image->data == NULL)
        {
                MessageBox(NULL, "Could not allocate memory for image", "ERROR",
MB_OK); fclose(fTGA); return NULL;
        }

        uint32_t pixelcount	= tga.Height * tga.Width;
        uint32_t currentpixel	= 0;
        uint32_t currentbyte	= 0;
        uint8_t * colorbuffer = (uint8_t *)malloc(tga.bytesPerPixel);

        do
        {
                uint8_t chunkheader = 0;

                if(fread(&chunkheader, sizeof(uint8_t), 1, fTGA) == 0)
                {
                        MessageBox(NULL, "Could not read RLE header", "ERROR",
MB_OK); if(fTGA != NULL)
                        {
                                fclose(fTGA);
                        }
                        if(image->data != NULL)
                        {
                                free(image->data);
                        }
                        return NULL;
                }

                if(chunkheader < 128)
                {
                        chunkheader++;
                        for(short counter = 0; counter < chunkheader; counter++)
                        {
                                if(fread(colorbuffer, 1, tga.bytesPerPixel,
fTGA) != tga.bytesPerPixel)
                                {
                                        MessageBox(NULL, "Could not read image
data", "ERROR", MB_OK);

                                        if(fTGA != NULL)
                                        {
                                                fclose(fTGA);
                                        }

                                        if(colorbuffer != NULL)
                                        {
                                                free(colorbuffer);
                                        }

                                        if(image->data != NULL)
                                        {
                                                free(image->data);
                                        }

                                        return NULL;
                                }

                                image->data[currentbyte		] =
colorbuffer[2]; image->data[currentbyte + 1	] = colorbuffer[1];
                                image->data[currentbyte + 2	] =
colorbuffer[0];

                                if(tga.bytesPerPixel == 4)
                                {
                                        image->data[currentbyte + 3] =
colorbuffer[3];
                                }

                                currentbyte += tga.bytesPerPixel;
                                currentpixel++;

                                if(currentpixel > pixelcount)
                                {
                                        MessageBox(NULL, "Too many pixels read",
"ERROR", NULL);

                                        if(fTGA != NULL)
                                        {
                                                fclose(fTGA);
                                        }

                                        if(colorbuffer != NULL)
                                        {
                                                free(colorbuffer);
                                        }

                                        if(image->data != NULL)
                                        {
                                                free(image->data);
                                        }

                                        return NULL;
                                }
                        }
                }
                else
                {
                        chunkheader -= 127;
                        if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) !=
tga.bytesPerPixel)
                        {
                                MessageBox(NULL, "Could not read from file",
"ERROR", MB_OK);

                                if(fTGA != NULL)
                                {
                                        fclose(fTGA);
                                }

                                if(colorbuffer != NULL)
                                {
                                        free(colorbuffer);
                                }

                                if(image->data != NULL)
                                {
                                        free(image->data);
                                }

                                return NULL;
                        }

                        for(short counter = 0; counter < chunkheader; counter++)
                        {
                                image->data[currentbyte		] =
colorbuffer[2]; image->data[currentbyte + 1	] = colorbuffer[1];
                                image->data[currentbyte + 2	] =
colorbuffer[0];

                                if(tga.bytesPerPixel == 4)
                                {
                                        image->data[currentbyte + 3] =
colorbuffer[3];
                                }

                                currentbyte += tga.bytesPerPixel;
                                currentpixel++;

                                if(currentpixel > pixelcount)
                                {
                                        MessageBox(NULL, "Too many pixels read",
"ERROR", NULL);

                                        if(fTGA != NULL)
                                        {
                                                fclose(fTGA);
                                        }

                                        if(colorbuffer != NULL)
                                        {
                                                free(colorbuffer);
                                        }

                                        if(image->data != NULL)
                                        {
                                                free(image->data);
                                        }

                                        return NULL;
                                }
                        }
                }
        }

        while(currentpixel < pixelcount);
        fclose(fTGA);
        return image;
}
*/
}  // End namespace OpenArena
