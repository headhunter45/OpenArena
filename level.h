/***************************************************************************
 *   Copyright (C) 2001-2023 by Tom Hicks                                  *
 *   headhunter3@gmail.com                                                 *
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

#ifndef OpenArena__level_h__
#define OpenArena__level_h__
// clang-format off
#include "config.h"

#include <cctype>
#include <cmath>
#include <cstdio>  //for file I/O
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "EventManager.h"
#include "bmp.h"
#include "camera.h"
#include "geometry.h"
#include "keys.h"
#include "mydefs.h"
#include "myglFont.h"
#include "myglTexture.h"
#include "opengl.h"
#include "player.h"
#include "strmanip.h"
#include "tga.h"
#include "vector.h"

namespace OpenArena {
const float piover180 = 0.0174532925f;
const std::string DEFAULT_TEXTURE_NAME = "oa/textures/default.bmp";
const unsigned int MAX_CONSOLE_LINES = 30;  // The max number of lines to be displayed in the console
const unsigned int MAX_CONSOLE_HISTORY_LINES =
    MAX_CONSOLE_LINES + 20;  // The max number of console lines to store in the history
const unsigned int MAX_CONSOLE_OUTPUT_LINES = MAX_CONSOLE_LINES;
const unsigned int MAX_OUTPUT_TEXT_LINES = 4;  // The max number of output lines to be displayed on the screen

enum { GL_MY_TEXTURE_CONSOLEBACKGROUND = 0, NUM_MENU_TEXTURES };

class Level {
 public:
  Level(EventManager* eventManager);
  ~Level();
  bool LoadMap(std::string mapname);
  bool LoadMap();
  void SaveMap(std::string mapname);
  bool LoadConfig(std::string cfgname);
  void LoadConfig();
  void SaveConfig(std::string cfgname);
  void Execute(std::string cmd);
  void LoadGLTextures();
  void Render();
  void UnloadMap();
  void UpdateConsole(char);
  uint32_t FPS();
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
  std::string nextLevel;
  Player* defaultPlayer;
  uint32_t numTextures;
  std::string* textureNames;

  std::string bgm;
  unsigned char bgmCDA;
  std::string gamedir;
  float gravity;
  bool mlook;
  bool showFPS;
  bool showConsole;
  bool sound;
  float turnSpeed;
  float moveSpeed;
  float mouseSpeed;
  unsigned char maxFPS;
  // Map
  Triangle* triangles;
  uint32_t numTriangles;
  std::vector<Player> players;
  //		std::vector<ENTITY> ents;
  std::vector<Texture*> textures;
  Texture menuTextures[NUM_MENU_TEXTURES];
  Window* _window;

  //	private:
  void ConsolePrint(std::string);

 private:
  EventManager* _eventManager;
  std::string consoleHistory[MAX_CONSOLE_HISTORY_LINES];
  std::string consoleOutput[MAX_CONSOLE_OUTPUT_LINES];
  std::string outputText[MAX_OUTPUT_TEXT_LINES];
};
}  // End namespace OpenArena
#endif  // End !defined(OpenArena__level_h__)
