#ifndef __myglTexture_h__
#define __myglTexture_h__

#include <string>
#include "datatypes.h"
#include "myGL.h"

using namespace std;

class GL_MY_TEXTURE
{
public:
	GL_MY_TEXTURE();
	~GL_MY_TEXTURE();
	string Filename();
	uint32 ID();
	bool Load(string filename);
	bool Load(string filename, uint32 min, uint32 mag);
	void Free();
	bool Loaded();
	bool operator<(const GL_MY_TEXTURE&);
	bool operator<=(const GL_MY_TEXTURE&);
	bool operator==(const GL_MY_TEXTURE&);
	bool operator!=(const GL_MY_TEXTURE&);
	bool operator>=(const GL_MY_TEXTURE&);
	bool operator>(const GL_MY_TEXTURE&);

private:
	uint32 minFilter;
	uint32 magFilter;
	string filename;
	uint32 id;
};

#endif