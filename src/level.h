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
#ifndef __LEVEL_H__
#define __LEVEL_H__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <iostream>

#if defined USE_GLX
#include <GL/gl.h>
#elif defined USE_AGL
#include <OpenGL/gl.h>
#elif defined USE_CGL
#include <OpenGL/gl.h>
#elif defined USE_WGL
#include <windows.h>
#include <GL/gl.h>
#endif

#include <cstdio>			//for file I/O

#include "mydefs.h"
#include "bmp.h"
#include "tga.h"
#include "list.h"
#ifdef WIN32
#include "../lib/bass.h"	//for audio in windows only this should be replaced by oa_audio
#endif
#include "vector.h"
#include "camera.h"
#include "geometry.h"
#include "myglFont.h"
#include "myglTexture.h"
#include "player.h"
#include "strmanip.h"
#include "keys.h"

using namespace std;
using OpenArena::Triangle;

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for piover180 here.
	 * 
	 * Write detailed description for piover180 here.
	 * 
	 * \remarks
	 * Write remarks for piover180 here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	const float piover180 = 0.0174532925f;
	/*!
	 * \brief
	 * Write brief comment for DEFAULT_TEXTURE_NAME here.
	 * 
	 * Write detailed description for DEFAULT_TEXTURE_NAME here.
	 * 
	 * \remarks
	 * Write remarks for DEFAULT_TEXTURE_NAME here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	const string DEFAULT_TEXTURE_NAME = "oa/textures/default.bmp";
	/*!
	 * \brief
	 * Write brief comment for MAX_CONSOLE_LINES here.
	 * 
	 * Write detailed description for MAX_CONSOLE_LINES here.
	 * 
	 * \remarks
	 * Write remarks for MAX_CONSOLE_LINES here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	const unsigned int MAX_CONSOLE_LINES = 30;  //The max number of lines to be displayed in the console
	/*!
	 * \brief
	 * Write brief comment for MAX_CONSOLE_HISTORY_LINES here.
	 * 
	 * Write detailed description for MAX_CONSOLE_HISTORY_LINES here.
	 * 
	 * \remarks
	 * Write remarks for MAX_CONSOLE_HISTORY_LINES here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	const unsigned int MAX_CONSOLE_HISTORY_LINES = MAX_CONSOLE_LINES + 20;	//The max number of console lines to store in the history
	/*!
	 * \brief
	 * Write brief comment for MAX_CONSOLE_OUTPUT_LINES here.
	 * 
	 * Write detailed description for MAX_CONSOLE_OUTPUT_LINES here.
	 * 
	 * \remarks
	 * Write remarks for MAX_CONSOLE_OUTPUT_LINES here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	const unsigned int MAX_CONSOLE_OUTPUT_LINES = MAX_CONSOLE_LINES;
	/*!
	 * \brief
	 * Write brief comment for MAX_OUTPUT_TEXT_LINES here.
	 * 
	 * Write detailed description for MAX_OUTPUT_TEXT_LINES here.
	 * 
	 * \remarks
	 * Write remarks for MAX_OUTPUT_TEXT_LINES here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	const unsigned int MAX_OUTPUT_TEXT_LINES = 4;  //The max number of output lines to be displayed on the screen
	
	/*!
	 * \brief
	 * Write brief comment for GL_MY_TEXTURE_CONSOLEBACKGROUND here.
	 */
	enum {GL_MY_TEXTURE_CONSOLEBACKGROUND=0, NUM_MENU_TEXTURES};
	
	class Level
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for Level here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Level here.
		 * 
		 * \remarks
		 * Write remarks for Level here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Level();
		/*!
		 * \brief
		 * Write brief comment for ~Level here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~Level here.
		 * 
		 * \remarks
		 * Write remarks for ~Level here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		~Level();
		/*!
		 * \brief
		 * Write brief comment for LoadMap here.
		 * 
		 * \param mapname
		 * Description of parameter mapname.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for LoadMap here.
		 * 
		 * \remarks
		 * Write remarks for LoadMap here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool LoadMap(string mapname);
		/*!
		 * \brief
		 * Write brief comment for LoadMap here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for LoadMap here.
		 * 
		 * \remarks
		 * Write remarks for LoadMap here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool LoadMap();
		/*!
		 * \brief
		 * Write brief comment for SaveMap here.
		 * 
		 * \param mapname
		 * Description of parameter mapname.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SaveMap here.
		 * 
		 * \remarks
		 * Write remarks for SaveMap here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SaveMap(string mapname);
		/*!
		 * \brief
		 * Write brief comment for LoadConfig here.
		 * 
		 * \param cfgname
		 * Description of parameter cfgname.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for LoadConfig here.
		 * 
		 * \remarks
		 * Write remarks for LoadConfig here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool LoadConfig(string cfgname);
		/*!
		 * \brief
		 * Write brief comment for LoadConfig here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for LoadConfig here.
		 * 
		 * \remarks
		 * Write remarks for LoadConfig here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void LoadConfig();
		void SaveConfig(string cfgname);
		/*!
		 * \brief
		 * Write brief comment for Execute here.
		 * 
		 * \param cmd
		 * Description of parameter cmd.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Execute here.
		 * 
		 * \remarks
		 * Write remarks for Execute here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Execute(string cmd);
		/*!
		 * \brief
		 * Write brief comment for LoadGLTextures here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for LoadGLTextures here.
		 * 
		 * \remarks
		 * Write remarks for LoadGLTextures here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void LoadGLTextures();
		/*!
		 * \brief
		 * Write brief comment for Render here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Render here.
		 * 
		 * \remarks
		 * Write remarks for Render here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Render();
		/*!
		 * \brief
		 * Write brief comment for UnloadMap here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for UnloadMap here.
		 * 
		 * \remarks
		 * Write remarks for UnloadMap here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void UnloadMap();
		/*!
		 * \brief
		 * Write brief comment for UpdateConsole here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for UpdateConsole here.
		 * 
		 * \remarks
		 * Write remarks for UpdateConsole here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void UpdateConsole(char);
		/*!
		 * \brief
		 * Write brief comment for FPS here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for FPS here.
		 * 
		 * \remarks
		 * Write remarks for FPS here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		uint32 FPS();
		/*!
		 * \brief
		 * Write brief comment for ParseCmds here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ParseCmds here.
		 * 
		 * \remarks
		 * Write remarks for ParseCmds here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void ParseCmds(const char*);
		void Print(int x, int y, const char* string, unsigned int set);
		/*!
		 * \brief
		 * Write brief comment for SetWindow here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetWindow here.
		 * 
		 * \remarks
		 * Write remarks for SetWindow here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetWindow(Window*);
		/*!
		 * \brief
		 * Write brief comment for GetWindow here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetWindow here.
		 * 
		 * \remarks
		 * Write remarks for GetWindow here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Window* GetWindow();
		
		/*Not Yet Implemented
		void PlayerConnect();		// implement later
		void PlayerDisconnect();	// implement later
		*/
		Screen screen;
		Font glFont;
		string nextLevel;
		Player* defaultPlayer;
		uint32 numTextures;
		string* textureNames;
		
		string bgm;
		#ifdef WIN32
		HSTREAM bgmStream;
		#endif
		unsigned char bgmCDA;
		string gamedir;
		float gravity;
		bool mlook;
		bool showFPS;
		bool showConsole;
		bool sound;
		float turnSpeed;
		float moveSpeed;
		float mouseSpeed;
		unsigned char maxFPS;
		//Map
		Triangle* triangles;
		uint32 numTriangles;
		list<Player> players;
//		list<ENTITY> ents;
		list<Texture*> textures;
		Texture menuTextures[NUM_MENU_TEXTURES];
		Window* _window;
	
	
//	private:
		/*!
		 * \brief
		 * Write brief comment for ConsolePrint here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ConsolePrint here.
		 * 
		 * \remarks
		 * Write remarks for ConsolePrint here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void ConsolePrint(string);
	private:
		string consoleHistory[MAX_CONSOLE_HISTORY_LINES];
		string consoleOutput[MAX_CONSOLE_OUTPUT_LINES];
		string outputText[MAX_OUTPUT_TEXT_LINES];
	};
};	
#endif
