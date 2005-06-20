#include "../include/myglTexture.h"

GL_MY_TEXTURE::GL_MY_TEXTURE()
{
	id=0xFFFFFFFF;
	filename = "";
	minFilter = GL_LINEAR;
	magFilter = GL_LINEAR;
}

GL_MY_TEXTURE::~GL_MY_TEXTURE()
{
	Free();
}

string GL_MY_TEXTURE::Filename()
{
	return filename;
}

GLuint GL_MY_TEXTURE::ID()
{
	return id;
}

bool GL_MY_TEXTURE::Loaded()
{
	return filename != "";
}

bool GL_MY_TEXTURE::Load(string fn)
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
		id=0xFFFFFFFF;
		return false;
	}
}

bool GL_MY_TEXTURE::Load(string fn, GLuint min, GLuint mag)
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

void GL_MY_TEXTURE::Free()
{
	if(Loaded())
	{
		FreeGLTexture(id);
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
		filename = "";
		id = 0xFFFFFFFF;
	}
}	

bool GL_MY_TEXTURE::operator<(const GL_MY_TEXTURE& rtOp)
{
	return id<rtOp.id;
}

bool GL_MY_TEXTURE::operator<=(const GL_MY_TEXTURE& rtOp)
{
	return id<=rtOp.id;
}

bool GL_MY_TEXTURE::operator==(const GL_MY_TEXTURE& rtOp)
{
	return id==rtOp.id;
}

bool GL_MY_TEXTURE::operator!=(const GL_MY_TEXTURE& rtOp)
{
	return id!=rtOp.id;
}

bool GL_MY_TEXTURE::operator>=(const GL_MY_TEXTURE& rtOp)
{
	return id>=rtOp.id;
}

bool GL_MY_TEXTURE::operator>(const GL_MY_TEXTURE& rtOp)
{
	return id>rtOp.id;
}
