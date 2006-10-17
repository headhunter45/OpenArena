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
#include "EventManager.h"

using namespace std;
using OpenArena::Triangle;

namespace OpenArena
{
	const float piover180 = 0.0174532925f;
	const string DEFAULT_TEXTURE_NAME = "oa/textures/default.bmp";
	const unsigned int MAX_CONSOLE_LINES = 30;  //The max number of lines to be displayed in the console
	const unsigned int MAX_CONSOLE_HISTORY_LINES = MAX_CONSOLE_LINES + 20;	//The max number of console lines to store in the history
	const unsigned int MAX_CONSOLE_OUTPUT_LINES = MAX_CONSOLE_LINES;
	const unsigned int MAX_OUTPUT_TEXT_LINES = 4;  //The max number of output lines to be displayed on the screen
	
	enum {GL_MY_TEXTURE_CONSOLEBACKGROUND=0, NUM_MENU_TEXTURES};
	
	class Level
	{
	public:
		Level(EventManager* eventManager);
		~Level();
		bool LoadMap(string mapname);
		bool LoadMap();
		void SaveMap(string mapname);
		bool LoadConfig(string cfgname);
		void LoadConfig();
		void SaveConfig(string cfgname);
		void Execute(string cmd);
		void LoadGLTextures();
		void Render();
		void UnloadMap();
		void UpdateConsole(char);
		uint32 FPS();
		void ParseCmds(const char*);
		void Print(int x, int y, const char* string, unsigned int set);
		void SetWindow(Window*);
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
		void ConsolePrint(string);
	private:
		EventManager* _eventManager;
		string consoleHistory[MAX_CONSOLE_HISTORY_LINES];
		string consoleOutput[MAX_CONSOLE_OUTPUT_LINES];
		string outputText[MAX_OUTPUT_TEXT_LINES];
	};
};	
#endif
