#ifndef __LEVEL_H__
#define __LEVEL_H__

#ifdef WIN32
#include <windows.h> //prolly used for alot but should be removed
#endif
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <iostream>
#ifdef WIN32
#include <GL/gl.h>
#endif
#ifdef __linux
#include <GL/gl.h>
#endif
#ifdef __APPLE___
#include <gl.h>
#endif
#include <cstdio>			//for file I/O

#include "mydefs.h"
#include "bmp.h"
#include "tga.h"
#include "list.h"
#ifdef WIN32
#include "bass.h"	//for audio in windows only this should be replaced by oa_audio
#endif
#include "vector.h"
#include "camera.h"
#include "entities.h"
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
		Level();
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
		list<ENTITY> ents;
		//list<GL_MY_TEXTURE> textures;
		Texture* textures;
		Texture menuTextures[NUM_MENU_TEXTURES];
		
	
	
//	private:
		void ConsolePrint(string);
	private:
		string consoleHistory[MAX_CONSOLE_HISTORY_LINES];
		string consoleOutput[MAX_CONSOLE_OUTPUT_LINES];
		string outputText[MAX_OUTPUT_TEXT_LINES];
	};
};	
#endif
