#ifndef __MYGL_H__
#define __MYGL_H__

#ifdef WIN32
#include <windows.h>	//Remove if possible
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#ifdef __linux
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#ifdef __APPLE__
#include <GL/gl.h>
#include <GL/glu.h>
#endif
//#include <gl/glaux.h>	//Hopefully nothing needs this remove if it works in windows
#include <string>
#include "datatypes.h"
#include "screen.h"
#include "tga.h"
#include "bmp.h"
#include "strmanip.h"
#include "window.h"

using namespace std;

#ifdef WIN32
//These this is windows specific
static HINSTANCE	hInstance;			// Application instance
#endif
extern OpenArena::Window g_Screen;
//This doesn't need to be here I think
//int InitGL(GLvoid);
namespace OpenArena
{
	bool LoadGLTexture(string , GLuint&, GLuint = GL_LINEAR, GLuint = GL_LINEAR);
	void FreeGLTexture(GLuint&);
};
#endif
