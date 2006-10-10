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
#include "myglTexture.h"
using namespace OpenArena;

namespace OpenArena
{
	Texture::Texture()
	{
		id=0xFFFFFFFF;
		filename = "";
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
	}
	
	Texture::~Texture()
	{
		Free();
	}
	
	string Texture::Filename()
	{
		return filename;
	}
	
	GLuint Texture::ID()
	{
		return id;
	}
	
	bool Texture::Loaded()
	{
		return filename != "";
	}
	
	bool Texture::Load(string fn)
	{
		if(Loaded())
			Free();
	
		if(LoadGLTexture(fn.c_str(), id, minFilter, magFilter))
		{
			filename = fn;
			return true;
		}
		else
		{
			id = 0xFFFFFFFF;
			return false;
		}
	}
	
	bool Texture::Load(string fn, GLuint min, GLuint mag)
	{
		if(Loaded())
			Free();
	
		if(LoadGLTexture(fn.c_str(), id, min, mag))
		{
			filename = fn;
			minFilter = min;
			magFilter = mag;
			return true;
		}
		else 
		{
			id=0xFFFFFFFF;
			return false;
		}
	}
	
	void Texture::Free()
	{
		if(Loaded())
		{
			//This is only temporarily removed for mac os x
			//TODO make this work on all operating systems
			//FreeGLTexture(id);
			minFilter = GL_LINEAR;
			magFilter = GL_LINEAR;
			filename = "";
			id = 0xFFFFFFFF;
		}
	}	
	
	bool Texture::operator<(const Texture& rtOp)
	{
		return id < rtOp.id;
	}
	
	bool Texture::operator<=(const Texture& rtOp)
	{
		return id<= rtOp.id;
	}
	
	bool Texture::operator==(const Texture& rtOp)
	{
		return id== rtOp.id;
	}
	
	bool Texture::operator!=(const Texture& rtOp)
	{
		return id!= rtOp.id;
	}
	
	bool Texture::operator>=(const Texture& rtOp)
	{
		return id>= rtOp.id;
	}
	
	bool Texture::operator>(const Texture& rtOp)
	{
		return id> rtOp.id;
	}
};
