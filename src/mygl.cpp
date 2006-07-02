
#include "mygl.h"
namespace OpenArena
{
	void FreeGLTexture(GLuint& texture)
	{
		glDeleteTextures(1, &texture);
	}
	
	bool LoadGLTexture(string fn, GLuint& texture, GLuint mag, GLuint min)
	{
		if(Right(tolower(fn), 4) == ".bmp")
		{
			TextureImage* texImage = NULL;
			if(texImage = BitmapImage::LoadBMP(fn.c_str()))
			{
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, texImage->sizeX, texImage->sizeY, 0, texImage->type, GL_UNSIGNED_BYTE, texImage->data);
				
				if(texImage)	//Just in case somehow the file was empty or unloadable
				{
					if(texImage->data)
						free(texImage->data);
					free(texImage);
				}
				return true;
			}	
			else
			{
				return false;
			}
		}
		else if(Right(tolower(fn), 4) == ".tga")
		{
			TextureImage* texImage = NULL;
			if(texImage = TargaImage::LoadTGA(fn.c_str()))
			{
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, texImage->sizeX, texImage->sizeY, 0, texImage->type, GL_UNSIGNED_BYTE, texImage->data);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				
				if(texImage)	//Just in case somehow the file was empty or unloadable
				{
					if(texImage->data)
						free(texImage->data);
					free(texImage);
				}
				return true;
			}	
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
};
	
OpenArena::Window* g_Screen = NULL;
