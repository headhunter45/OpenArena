#ifndef __MYGL_H__
#define __MYGL_H__

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <string>
#include "screen.h"
#include "tga.h"
#include "bmp.h"
#include "strmanip.h"

using namespace std;

static HDC			hDC=NULL;			// Private GDI device context
static HGLRC		hRC=NULL;			// Permanent rendering context
static HINSTANCE	hInstance;			// Application instance
static SCREEN g_Screen;
int InitGL(GLvoid);

bool LoadGLTexture(string , unsigned int&, int = GL_LINEAR, int = GL_LINEAR);
void FreeGLTexture(unsigned int&);
#endif

