#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <windows.h>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>		//for auxDIBImageLoad
#include <stdio.h>			//for file I/O

#include "mydefs.h"
#include "bmp.h"
#include "tga.h"
#include "list.h"
#include "bass.h"			
#include "vector.h"
#include "camera.h"
#include "entities.h"
#include "geometry.h"
#include "myglFont.h"
#include "myglTexture.h"
#include "player.h"
#include "strmanip.h"

using namespace std;

const float piover180 = 0.0174532925f;
const string DEFAULT_TEXTURE_NAME = "oa/textures/default.tga";
const unsigned int MAX_CONSOLE_LINES = 30;  //The max number of lines to be displayed in the console
const unsigned int MAX_CONSOLE_HISTORY_LINES = MAX_CONSOLE_LINES + 20;	//The max number of console lines to store in the history
const unsigned int MAX_CONSOLE_OUTPUT_LINES = MAX_CONSOLE_LINES;
const unsigned int MAX_OUTPUT_TEXT_LINES = 4;  //The max number of output lines to be displayed on the screen

enum {GL_MY_TEXTURE_CONSOLEBACKGROUND=0, NUM_MENU_TEXTURES};

class LEVEL
{
public:
	LEVEL();
	~LEVEL();
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
	void ParseCmds(LPSTR);

	void Print(int x, int y, const char* string, unsigned int set);

	/*Not Yet Implemented
	void PlayerConnect();		// implement later
	void PlayerDisconnect();	// implement later
	*/
	SCREEN screen;
	GLFontClass glFont;
	string nextLevel;
	PLAYER* defaultPlayer;
	uint32 numTextures;
	string* textureNames;
	
	string bgm;
	HSTREAM bgmStream;
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
	TRIANGLE* triangles;
	uint32 numTriangles;
	list<PLAYER> players;
	list<ENTITY> ents;
	//list<GL_MY_TEXTURE> textures;
	GL_MY_TEXTURE* textures;
	GL_MY_TEXTURE menuTextures[NUM_MENU_TEXTURES];
	


private:
	void ConsolePrint(string);
	string consoleHistory[MAX_CONSOLE_HISTORY_LINES];
	string consoleOutput[MAX_CONSOLE_OUTPUT_LINES];
	string outputText[MAX_OUTPUT_TEXT_LINES];
};
#endif