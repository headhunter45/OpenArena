#ifndef __main_h__
#define __main_h__

#include <windows.h>			// Header file for windows
#include <stdio.h>				// Header file for standard input/output
#include <gl\gl.h>				// Header file for OpenGL32 library
#include <gl\glu.h>				// Header file for Glu32 library
#include <gl\glaux.h>			// Header file for GLaux library
#include <math.h>

#include "camera.h"
#include "level.h"
#include "myGL.h"
#include "WorldDefs.h"
#include "mydefs.h"

#pragma warning(disable: 4786)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables

static bool		keys[256];			// Array for which keys are down now
static bool		keys2[256];			// Array for which keys are were down already
static bool		active=true;		// Is window active flag
static bool		fullscreen=true;	// Is window fullscreen flag
//static bool		showConsole = false;// Do we need to draw the console



//static SCREEN g_Screen = {800,600,16,1,"OpenArena"};
static POINT mpos;
static float lastTime = 0.0f;		// This will hold the time from the last frame
static float currentTime;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

void InitControls();				// Sets up player controls
int InitGL();						// All setup for OpenGL goes here
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);	// Resize and initialize the GL window
GLvoid KillGLWindow(GLvoid);		//Properly kill the window
bool CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag);

#endif
