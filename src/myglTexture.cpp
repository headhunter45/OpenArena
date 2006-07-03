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
