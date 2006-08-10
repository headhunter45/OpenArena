#ifndef __main_h__
#define __main_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32
#include <windows.h>			// Header file for windows
#endif
#include <cstdio>			// Header file for standard input/output
#ifdef WIN32
#include <GL/gl.h>			// Header file for OpenGL32 library
#include <GL/glu.h>			// Header file for Glu32 library
#endif
#ifdef __linux
#include <GL/gl.h>			// Header file for OpenGL32 library
#include <GL/glu.h>			// Header file for Glu32 library
#endif
#ifdef __APPLE__
#include <GL/gl.h>				// Header file for OpenGL32 library
#include <GL/glu.h>				// Header file for Glu32 library
#endif
#include <math.h>

#include "camera.h"
#include "level.h"
#include "mygl.h"
#include "worlddefs.h"
#include "mydefs.h"
#include "screen.h"
#include "window.h"
#include "vector.h"
#pragma warning(disable: 4786)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables

static bool		keys[256];			// Array for which keys are down now
static bool		keys2[256];			// Array for which keys are were down already
static bool		active=true;		// Is window active flag
static bool		fullscreen=true;	// Is window fullscreen flag
//static bool		showConsole = false;// Do we need to draw the console
static OpenArena::Vec2i	g_mousePosition;



#ifdef WIN32
static POINT mpos;
#endif
static float lastTime = 0.0f;		// This will hold the time from the last frame
static float currentTime;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Declarations

//This shouldn't need to be here
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

/*!
 * \brief
 * Write brief comment for InitControls here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for InitControls here.
 * 
 * \remarks
 * Write remarks for InitControls here.
 * 
 * \see
 * Separate items with the '|' character.
 */
void InitControls();				// Sets up player controls
/*!
 * \brief
 * Write brief comment for InitGL here.
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for InitGL here.
 * 
 * \remarks
 * Write remarks for InitGL here.
 * 
 * \see
 * Separate items with the '|' character.
 */
int InitGL();						// All setup for OpenGL goes here
/*!
 * \brief
 * Write brief comment for ReSizeGLScene here.
 * 
 * \param width
 * Description of parameter width.
 * 
 * \param height
 * Description of parameter height.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for ReSizeGLScene here.
 * 
 * \remarks
 * Write remarks for ReSizeGLScene here.
 * 
 * \see
 * Separate items with the '|' character.
 */
void ReSizeGLScene(GLsizei width, GLsizei height);	// Resize and initialize the GL window

#endif
