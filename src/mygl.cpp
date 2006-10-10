/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks   *
 *   tomhicks@cse.buffalo.edu   *
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
			if(texImage = LoadBMP(fn.c_str()))
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
			if(texImage = LoadTGA(fn.c_str()))
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
	
OpenArena::Window g_Screen;
