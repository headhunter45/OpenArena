/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks   *
 *   tomhicks@cse.buffalo.edu   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef __window_h__
#define __window_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include "screen.h"

#if defined USE_GLX
	#include <GL/gl.h>
	#include <GL/glu.h> //maybe not necessary
	#include <GL/glx.h>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/keysym.h>
	#if defined HAVE_XF86VIDMODE
		#include <X11/extensions/xf86vmode.h>
	#endif
#elif defined USE_AGL
	#include <AGL/agl.h>
	#include <OpenGL/gl.h>
#elif defined USE_CGL
	#include <OpenGL/OpenGL.h>
	#include <OpenGL/gl.h>
#elif defined USE_WGL
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#ifdef WIN32
#endif
#include "vector.h"

namespace OpenArena
{	
	/*!
	 * \brief
	 * Write brief comment for Window here.
	 * 
	 * Write detailed description for Window here.
	 * 
	 * \remarks
	 * Write remarks for Window here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Window: public Screen
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for Resizer here.
		 * 
		 * Write detailed description for Resizer here.
		 * 
		 * \remarks
		 * Write remarks for Resizer here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		class Resizer
		{
		public:
			/*!
			 * \brief
			 * Write brief comment for Resize here.
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
			 * Write detailed description for Resize here.
			 * 
			 * \remarks
			 * Write remarks for Resize here.
			 * 
			 * \see
			 * Separate items with the '|' character.
			 */
			void Resize(GLsizei width, GLsizei height);
		};
		
		/*!
		 * \brief
		 * Write brief comment for Initializer here.
		 * 
		 * Write detailed description for Initializer here.
		 * 
		 * \remarks
		 * Write remarks for Initializer here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		class Initializer
		{
		public:
			/*!
			 * \brief
			 * Write brief comment for Initialize here.
			 * 
			 * \returns
			 * Write description of return value here.
			 * 
			 * \throws <exception class>
			 * Description of criteria for throwing this exception.
			 * 
			 * Write detailed description for Initialize here.
			 * 
			 * \remarks
			 * Write remarks for Initialize here.
			 * 
			 * \see
			 * Separate items with the '|' character.
			 */
			int Initialize();
		};
	
	public:
		/*!
		 * \brief
		 * Write brief comment for Window here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Window here.
		 * 
		 * \remarks
		 * Write remarks for Window here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Window();
		/*!
		 * \brief
		 * Write brief comment for ~Window here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~Window here.
		 * 
		 * \remarks
		 * Write remarks for ~Window here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		~Window();
		/*!
		 * \brief
		 * Write brief comment for Close here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Close here.
		 * 
		 * \remarks
		 * Write remarks for Close here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Close();
		/*!
		 * \brief
		 * Write brief comment for Open here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Open here.
		 * 
		 * \remarks
		 * Write remarks for Open here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool Open();
		/*!
		 * \brief
		 * Write brief comment for Open here.
		 * 
		 * \param title
		 * Description of parameter title.
		 * 
		 * \param width
		 * Description of parameter width.
		 * 
		 * \param height
		 * Description of parameter height.
		 * 
		 * \param bits
		 * Description of parameter bits.
		 * 
		 * \param fullscreenflag
		 * Description of parameter fullscreenflag.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Open here.
		 * 
		 * \remarks
		 * Write remarks for Open here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool Open(string title, int width, int height, int bits, bool fullscreenflag);	//make that string a const char* after this works
		/*!
		 * \brief
		 * Write brief comment for SetInitializer here.
		 * 
		 * \param initializer
		 * Description of parameter initializer.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetInitializer here.
		 * 
		 * \remarks
		 * Write remarks for SetInitializer here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetInitializer(Initializer* initializer);
		/*!
		 * \brief
		 * Write brief comment for SetResizer here.
		 * 
		 * \param resizer
		 * Description of parameter resizer.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetResizer here.
		 * 
		 * \remarks
		 * Write remarks for SetResizer here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		/*!
		 * \brief
		 * Write brief comment for SetResizer here.
		 * 
		 * \param resizer
		 * Description of parameter resizer.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetResizer here.
		 * 
		 * \remarks
		 * Write remarks for SetResizer here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetResizer(Resizer* resizer);
		/*!
		 * \brief
		 * Write brief comment for SwapBuffers here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SwapBuffers here.
		 * 
		 * \remarks
		 * Write remarks for SwapBuffers here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SwapBuffers();
		/*!
		 * \brief
		 * Write brief comment for Resize here.
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
		 * Write detailed description for Resize here.
		 * 
		 * \remarks
		 * Write remarks for Resize here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Resize(GLsizei width, GLsizei height);
		/*!
		 * \brief
		 * Write brief comment for GetMousePosition here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetMousePosition here.
		 * 
		 * \remarks
		 * Write remarks for GetMousePosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i GetMousePosition();
		/*!
		 * \brief
		 * Write brief comment for SetMousePosition here.
		 * 
		 * \param pos
		 * Description of parameter pos.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetMousePosition here.
		 * 
		 * \remarks
		 * Write remarks for SetMousePosition here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetMousePosition(Vec2i pos);

		#ifdef USE_GLX
			Display* GetDisplay();
		#endif
	private:
		#ifdef USE_GLX
			Cursor CreateWindowedCursor();
			Cursor CreateFullscreenCursor();
			int screen;
			::Window window;
			GLXContext hRC;
			XSetWindowAttributes attributes;
			bool doubleBuffered;
			#if defined HAVE_XF86VIDMODE
				XF86VidModeModeInfo vidMode;
			#endif
			int x, y;
			Display* display;			
		#elif defined USE_WGL
			HGLRC glContext;
			HWND window;
			HDC deviceContext;
			HINSTANCE instance;
		#endif
		Resizer* _resizer;
		Initializer* _initializer;
	};
};

#if defined USE_GLX
static int attrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};
static int attrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};
#elif defined USE_WGL
/*!
 * \brief
 * Write brief comment for WndProc here.
 * 
 * \param 
 * Description of parameter .
 * 
 * \param 
 * Description of parameter .
 * 
 * \param 
 * Description of parameter .
 * 
 * \param 
 * Description of parameter .
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for WndProc here.
 * 
 * \remarks
 * Write remarks for WndProc here.
 * 
 * \see
 * Separate items with the '|' character.
 */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif

#endif
