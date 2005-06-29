#ifndef __myglTexture_h__
#define __myglTexture_h__

#include <string>
#include "datatypes.h"
#include "mygl.h"

using namespace std;

namespace OpenArena
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		string Filename();
		GLuint ID();
		bool Load(string filename);
		bool Load(string filename, GLuint min, GLuint mag);
		void Free();
		bool Loaded();
		bool operator<(const Texture&);
		bool operator<=(const Texture&);
		bool operator==(const Texture&);
		bool operator!=(const Texture&);
		bool operator>=(const Texture&);
		bool operator>(const Texture&);
	
	private:
		GLuint minFilter;
		GLuint magFilter;
		string filename;
		GLuint id;
	};
};	
#endif
