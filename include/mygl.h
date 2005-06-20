#ifndef __MYGL_H__
#define __MYGL_H__

#ifdef WIN32
#include <windows.h>	//Remove if possible
#endif
#include <GL/gl.h>
#include <GL/glu.h>
//#include <gl/glaux.h>	//Hopefully nothing needs this remove if it works in windows
#include <string>
#include "datatypes.h"
#include "screen.h"
#include "tga.h"
#include "bmp.h"
#include "strmanip.h"

using namespace std;

#ifdef WIN32
//These three are windows specific
static HDC			hDC=NULL;			// Private GDI device context
static HGLRC		hRC=NULL;			// Permanent rendering context
static HINSTANCE	hInstance;			// Application instance
#endif
static SCREEN g_Screen;
int InitGL(GLvoid);

bool LoadGLTexture(string , GLuint&, GLuint = GL_LINEAR, GLuint = GL_LINEAR);
void FreeGLTexture(GLuint&);
#endif
