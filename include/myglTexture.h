#ifndef __myglTexture_h__
#define __myglTexture_h__

#include <string>
#include "datatypes.h"
#include "mygl.h"

using namespace std;

class GL_MY_TEXTURE
{
public:
	GL_MY_TEXTURE();
	~GL_MY_TEXTURE();
	string Filename();
	GLuint ID();
	bool Load(string filename);
	bool Load(string filename, GLuint min, GLuint mag);
	void Free();
	bool Loaded();
	bool operator<(const GL_MY_TEXTURE&);
	bool operator<=(const GL_MY_TEXTURE&);
	bool operator==(const GL_MY_TEXTURE&);
	bool operator!=(const GL_MY_TEXTURE&);
	bool operator>=(const GL_MY_TEXTURE&);
	bool operator>(const GL_MY_TEXTURE&);

private:
	GLuint minFilter;
	GLuint magFilter;
	string filename;
	GLuint id;
};

#endif
