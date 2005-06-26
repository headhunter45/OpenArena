#ifndef __main_h__
#define __main_h__

#ifdef WIN32
#include <windows.h>			// Header file for windows
#endif
#include <cstdio>				// Header file for standard input/output
#include <GL/gl.h>				// Header file for OpenGL32 library
#include <GL/glu.h>				// Header file for Glu32 library
#include <math.h>

#include "camera.h"
#include "level.h"
#include "mygl.h"
#include "worlddefs.h"
#include "mydefs.h"
#include "screen.h"
#include "window.h"
#pragma warning(disable: 4786)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables

static bool		keys[256];			// Array for which keys are down now
static bool		keys2[256];			// Array for which keys are were down already
static bool		active=true;		// Is window active flag
static bool		fullscreen=true;	// Is window fullscreen flag
//static bool		showConsole = false;// Do we need to draw the console



//static SCREEN g_Screen = {800,600,16,1,"OpenArena"};
#ifdef WIN32
static POINT mpos;
#endif
static float lastTime = 0.0f;		// This will hold the time from the last frame
static float currentTime;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Declarations

//This shouldn't need to be here
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

void InitControls();				// Sets up player controls
int InitGL();						// All setup for OpenGL goes here
void ReSizeGLScene(GLsizei width, GLsizei height);	// Resize and initialize the GL window



#endif
