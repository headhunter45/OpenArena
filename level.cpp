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

// clang-format off
#include "level.h"
#include <sstream>
#include <vector>
#include "logger.h"
#include "version.h"

// clang-format on

namespace {
// using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostringstream;
using std::string;
using std::to_string;
using std::vector;
}  // End namespace

namespace OpenArena {

// set consoleHistory
Level::Level(EventManager* eventManager)
    : _eventManager(eventManager),
      _window(nullptr),
      showConsole(false),
      showFPS(false),
      defaultPlayer(nullptr),
      numTextures(0),
      nextLevel("intro.map"),
      gamedir("oa/"),
      sound(true),
      numTriangles(0),
      mouseSpeed(5),
      turnSpeed(1.0f),
      mlook(true) {
  screen.SetName(OPENARENA_VERSION);
  defaultPlayer = new Player;
}

Level::~Level() {
  if (defaultPlayer) {
    delete defaultPlayer;
    defaultPlayer = NULL;
  }
}

bool Level::LoadMap(string mapname) {
  string method_name = "OpenArena::Level::LoadMap(string) ";
  ifstream input;
  string readBuffer;

  Logger::LogDebug(method_name + "Loading map: " + mapname);
  mapname = gamedir + "maps/" + mapname;

  if (tolower(Right(mapname, 4)) != ".map") mapname = mapname + ".map";

  input.open(mapname.c_str());

  if (!input) {
    string message = "Unable to load level file " + mapname + " doesn't exist.";
    Logger::LogError(method_name + message);
    Logger::LogDebug(method_name + "returning false.");
    return false;
  } else {
    Logger::LogDebug(method_name + "Map file \"" + mapname + "\" opened successfully.");
    ConsolePrint("Map file \"" + mapname + "\" opened successfully.");
  }

  // Gravity
  input >> readBuffer;
  gravity = (float)atof(readBuffer.c_str());

  // Number of triangles
  input >> readBuffer;
  numTriangles = Integer(readBuffer);

  // Triangle Data
  triangles = new Triangle[numTriangles];
  for (unsigned int i = 0; i < numTriangles; i++) {
    // TextureID
    input >> readBuffer;
    triangles[i].texID = Integer(readBuffer);

    for (unsigned int i2 = 0; i2 < 3; i2++) {
      // Vertex Data
      input >> readBuffer;
      triangles[i].vertecies[i2].coordinates.x = atof(readBuffer.c_str());
      input >> readBuffer;
      triangles[i].vertecies[i2].coordinates.y = atof(readBuffer.c_str());
      input >> readBuffer;
      triangles[i].vertecies[i2].coordinates.z = atof(readBuffer.c_str());
      input >> readBuffer;
      triangles[i].vertecies[i2].textureCoordinates.x = (float)atof(readBuffer.c_str());
      input >> readBuffer;
      triangles[i].vertecies[i2].textureCoordinates.y = (float)atof(readBuffer.c_str());
    }

    // Normal
    input >> readBuffer;

    triangles[i].normal.x = atof(readBuffer.c_str());
    input >> readBuffer;
    triangles[i].normal.y = atof(readBuffer.c_str());
    input >> readBuffer;
    triangles[i].normal.z = atof(readBuffer.c_str());
  }
  char lpszNumTriangles[6];
  sprintf(lpszNumTriangles, "%d", numTriangles);
  ConsolePrint(lpszNumTriangles + string(" triangles successfully read."));

  // Number of textures;
  input >> readBuffer;
  numTextures = Integer(readBuffer);
  Logger::LogDebug("read num_textures = " + to_string(numTextures));

  // Texture data
  textureNames = new string[numTextures];
  for (unsigned int i = 0; i < numTextures; i++) {
    input >> textureNames[i];
    Logger::LogDebug("read texture name = " + textureNames[i]);
  }
  LoadGLTextures();
  Logger::LogDebug("after LoadGLTextures()");
  // Copy loaded textures to the individual triangles.
  for (uint32_t i = 0; i < numTriangles; i++) {
    Triangle& triangle = triangles[i];
    triangle.texture = *textures[triangle.texID];
  }
  char lpszNumTextures[6];
  sprintf(lpszNumTextures, "%d", numTextures);
  ConsolePrint(lpszNumTextures + string(" textures successfully read"));

  Logger::LogDebug("about to read bgm from file");
  // BGM
  input >> bgm;

  // Build display list
  Logger::LogDebug(string("sound is ") + (sound ? "true" : "false"));
  // Sound
  if (sound) {
    ConsolePrint("Starting sound");
    if (bgm.length() >= 4) {
      if (toupper(bgm[0]) == 'C' && toupper(bgm[1]) == 'D' && toupper(bgm[2]) == 'A') {
        bgmCDA = Integer(bgm.substr(3, bgm.length()));
      } else {
        bgmCDA = 0;
        string tmpstr = gamedir + "music/bgm/" + bgm;
        // This needs to be abstracted somehow
      }
    }
    ConsolePrint("Sound init complete");
  } else {
    ConsolePrint("Sound disabled");
  }
  Logger::LogDebug(method_name + "returning true.");

  return true;
}

bool Level::LoadMap() {
  return LoadMap(nextLevel);
}

void Level::SaveMap(string mapname) {
  ofstream output;

  mapname = gamedir + "maps/" + mapname;

  if (tolower(Right(mapname, 4)) != ".map") mapname = mapname + ".map";

  output.open(mapname.c_str());

  if (!output) {
    Logger::LogError("Unable to save level file " + mapname + " already exists.");
    return;
  }

  // Gravity
  output << gravity << endl;

  // Number of triangles
  output << numTriangles << endl;

  // Triangle Data
  for (unsigned int i = 0; i < numTriangles; i++) {
    output << triangles[i].texID << endl;

    for (unsigned int i2 = 0; i2 < 3; i2++) {
      output << triangles[i].vertecies[i2].coordinates.x << " " << triangles[i].vertecies[i2].coordinates.y << " "
             << triangles[i].vertecies[i2].coordinates.z << " " << triangles[i].vertecies[i2].textureCoordinates.x
             << " " << triangles[i].vertecies[i2].textureCoordinates.y << endl;
    }

    output << triangles[i].normal.x << " " << triangles[i].normal.y << " " << triangles[i].normal.z << endl;
  }

  // Number of textures;
  output << numTextures;

  // Texture data
  for (unsigned int i = 0; i < numTextures; i++) {
    output << textureNames[i];
  }

  // BGM
  output << bgm;
}

string to_string(const Vertex& value) {
  // Vertex {x: 12, y: 34, z: 56, u: 0.2, v: 0.4}
  ostringstream os;
  os << "Vertex {x: " << value.coordinates.x << ", y: " << value.coordinates.y << ", z: " << value.coordinates.z
     << ", u: " << value.textureCoordinates.x << ", v: " << value.textureCoordinates.y << "}";
  return os.str();
}

string to_string(const Texture& value) {
  /*
Texture {
    filename: "",
    id: 12,
    is_loaded: true/false
},
  */
  ostringstream os;
  os << "Texture {filename: \"" << value.Filename() << "\", id: " << value.ID()
     << ", is_loaded: " << (value.Loaded() ? "true" : "false");
  return os.str();
}

string to_string(const Vec3f& value) {
  /*
Vec3f {x: 1, y: 2, z: 3}
  */
  ostringstream os;
  os << "Vec3f {x: " << value.x << ", y: " << value.y << ", z: " << value.z << "}";
  return os.str();
}

string to_string(const Triangle& triangle) {
  /*
Triangle {
  normal: {x: 12, y: 34, z: 56}
  tex_id: 12,
  texture: {
      filename: "",
      id: 12,
      is_loaded: true/false
  },
  vertecies: [
      0: {x: 12, y: 34, z: 56, u: 0.2, v: 0.4},
      1: {x: 12, y: 34, z: 56, u: 0.2, v: 0.4},
      2: {x: 12, y: 34, z: 56, u: 0.2, v: 0.4},
  ]
}
  */
  ostringstream os;
  os << "Triangle {normal: " + to_string(triangle.normal) << ", tex_id: " << triangle.texID
     << ", texture: " << to_string(triangle.texture) << ", vertices: [";
  // TODO: Make this a range based for loop after making vertices a std::array or std::vector.
  for (int i = 0; i < 3; i++) {
    os << std::to_string(i) << ": " << to_string(triangle.vertecies[i]) << ",";
  }
  os << "]}";
  return os.str();
}

int num_renders = 0;

void Level::Render() {
  const string method_name = "OpenArena::Level::Render() ";
  static int num_renders = 0;
  num_renders++;
  if (num_renders > 5) {
    return;
  }
  Logger::LogDebug(method_name + "Entered");
  glPushMatrix();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // Move the camera to where the player is
  defaultPlayer->camera.Look();

  Logger::LogDebug(method_name + "Rendering " + std::to_string(numTriangles) + " triangles.");
  for (uint32_t i = 0; i < numTriangles; i++) {
    Triangle triangle = triangles[i];
    Logger::LogDebug(method_name + "Rendering a " + to_string(triangle));

    glBindTexture(GL_TEXTURE_2D, triangles[i].texture.ID());  // Bind this triangle's texture
    glBegin(GL_TRIANGLES);
    for (uint32_t i2 = 0; i2 < 3; i2++) {
      glTexCoord2f(triangles[i].vertecies[i2].textureCoordinates.x, triangles[i].vertecies[i2].textureCoordinates.y);
      glVertex3f((GLfloat)triangles[i].vertecies[i2].coordinates.x, (GLfloat)triangles[i].vertecies[i2].coordinates.y,
                 (GLfloat)triangles[i].vertecies[i2].coordinates.z);
    }
    glEnd();
  }
  glPopMatrix();

  // Draw HUD
  // ummm nothing here yet

  // Draw FPS
  // This may not work yet
  if (showFPS) {
    char fps[20];
    sprintf(fps, "fps %d", FPS());
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1, 1, 1);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glFont.Print(glFont.ScreenWidth() - 120, glFont.ScreenHeight() - 30, fps, 0);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
  }

  if (showConsole) {
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1, 1, 1);

    // disable lighting and depth testing
    glDisable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].ID());
    // glBindTexture(GL_TEXTURE_2D, 4);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, screen.GetWidth(), 0, screen.GetHeight(), -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2i(0, screen.GetHeight() / 2);
    glTexCoord2f(0, 1);
    glVertex2i(0, screen.GetHeight());
    glTexCoord2f(1, 1);
    glVertex2i(screen.GetWidth(), screen.GetHeight());
    glTexCoord2f(1, 0);
    glVertex2i(screen.GetWidth(), screen.GetHeight() / 2);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    // enable blending
    glEnable(GL_BLEND);

    // render the console background
    // render the console output text
    unsigned int i;
    for (i = 0; i < MAX_CONSOLE_LINES - 1; i++) {
      Print(30, glFont.ScreenHeight() - i * 20, consoleOutput[MAX_CONSOLE_LINES - i - 2].c_str(), 0);
    }

    // Render the currently typed command
    Print(30, glFont.ScreenHeight() - i * 20, consoleHistory[0].c_str(), 0);

    // disable blending
    glDisable(GL_BLEND);

    // re-enable lighting and depth testing
    // glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
  }
}

void Level::UnloadMap() {
  // Stop audio
  //  TODO: Free audio resources.
  // Delete display list

  // Free all polygon data
  if (triangles) {
    delete[] triangles;
    triangles = NULL;
  }

  // Free all map textures
  textures.clear();

  // Free the array of texture names
  if (textureNames) {
    delete[] textureNames;
    textureNames = NULL;
  }
}

void Level::LoadGLTextures() {
  Logger::LogDebug("In LoadGLTextures");
  string file_name;
  if (_window != nullptr) {
    Logger::LogDebug("_window is not null");
    textures.clear();

    for (uint32_t i = 0; i < numTextures; i++) {
      Texture* texture = new Texture();
      file_name = gamedir + "textures/" + textureNames[i];
      Logger::LogDebug("loading texture from " + file_name);
      if (!texture->Load(file_name)) {
        Logger::LogDebug("falling back to " + DEFAULT_TEXTURE_NAME);
        texture->Load(DEFAULT_TEXTURE_NAME);
      }
      Logger::LogDebug("texture loaded");
      textures[i] = texture;
    }

    file_name = gamedir + "textures/menu/font.bmp";
    Logger::LogDebug("Loading font from " + file_name);
    if (!glFont.BuildFont(file_name.c_str())) {
      Logger::LogDebug("Falling back to oa/textures/menu/font.bmp");
      glFont.BuildFont("oa/textures/menu/font.bmp");
    }

    // Load the console background image
    file_name = gamedir + "textures/menu/con_back.tga";
    Logger::LogDebug("Loading console background from " + file_name);
    if (!menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].Load(file_name)) {
      Logger::LogDebug("Falling back to oa/textures/menu/con_back.bmp");
      menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].Load("oa/textures/menu/con_back.bmp");
    }
  }
}

uint32_t Level::FPS() {
  static uint32_t fps = 0;
  static uint32_t fps2 = 0;
  static float last = 0.0f;  // might need to change to double

// hmmm what the hell is this called in linux I should possibly abstract this
#ifdef WIN32
  float time = GetTickCount() * .001f;
#else
  float time = 0;
#endif

  ++fps;

  if (time > last + 1) {
    last = time;
    fps2 = fps;
    fps = 0;
  }
  return fps2;
}

void Level::Execute(string cmd) {
  string command;

  uint32_t i = 0xFFFFFFFF;
  while (word(cmd, ++i) != "") {
    command = tolower(word(cmd, i));

    if (command == "set") {
      command = tolower(word(cmd, ++i));

      if (command == "turnspeed") {
        turnSpeed = (float)atof(word(cmd, ++i).c_str());  // Floating(word(cmd, ++i));
      } else if (command == "movespeed") {
        moveSpeed = (float)atof(word(cmd, ++i).c_str());  // FLoating(word(cmd, ++i));
      } else if (command == "mousespeed") {
        mouseSpeed = (float)atof(word(cmd, ++i).c_str());
      } else if (command == "mouselook") {
        mlook = Truth(word(cmd, ++i));
      } else if (command == "maxfps") {
        maxFPS = Integer(word(cmd, ++i));
      } else if (command == "sound") {
        sound = Truth(word(cmd, ++i));
      } else if (command == "game") {
        gamedir = word(cmd, ++i);
      } else if (command == "screenwidth") {
        screen.SetWidth(Integer(word(cmd, ++i)));
      } else if (command == "screenheight") {
        screen.SetHeight(Integer(word(cmd, ++i)));
      } else if (command == "fullscreen") {
        screen.SetFullscreen(Truth(word(cmd, ++i)));
      } else if (command == "colordepth") {
        screen.SetColorDepth(Integer(word(cmd, ++i)));
      } else {
        ConsolePrint("Variable " + command + " doesn't exist");
      }
    } else if (command == "bind") {
      command = tolower(word(cmd, ++i));
      string key = tolower(word(cmd, ++i));
      if (ControlScheme::GetAction(command.c_str()) == OpenArena::ControlScheme::ACTION_NONE) {
        ConsolePrint("No action identified by " + command);
      } else if (GetKey(key.c_str()) == OpenArena::KEY_UNKNOWN) {
        ConsolePrint("No key identified by " + key);
      } else {
        defaultPlayer[0].controls.Bind(GetKey(key.c_str()), ControlScheme::GetAction(command.c_str()));
      }
    } else if (command == "map" || command == "map_load") {
      nextLevel = word(cmd, ++i);
      UnloadMap();
      if (!LoadMap()) {
        ConsolePrint("Unable to load level " + command);
        nextLevel = "intro.map";
        LoadMap();
      }
    } else if (command == "unbind") {
      command = tolower(word(cmd, ++i));

      if (command == "all") {
        defaultPlayer[0].controls.UnBindAll();
      } else {
        defaultPlayer[0].controls.UnBind(GetKey(command.c_str()));
      }
    } else if (command == "exec" || command == "config_load") {
      command = tolower(word(cmd, ++i));
      if (!LoadConfig(command)) {
        ConsolePrint("Unable to load config file " + word(cmd, i));
      }
    } else if (command == "map_save") {
      command = tolower(word(cmd, ++i));
      SaveMap(command);
    } else if (command == "config_save") {
      command = tolower(word(cmd, ++i));
      SaveConfig(command);
    }
    /*
    else if(command == "map_add_triangle")
    {
            if(triangles != NULL)
            {
                    TRIANGLE* temp = triangles;
                    triangles = new TRIANGLE[numTriangles + 1];
                    for(int i=0; i<numTriangles; i++)
                    {
                            triangles[i] = temp[i];
                    }

                    triangles[numTriangles].texID = 0;
                    for(int i=0; i<3; i++)
                    {
                            triangles[numTriangles].vertecies[i].x = 0;
                            triangles[numTriangles].vertecies[i].y = 0;
                            triangles[numTriangles].vertecies[i].z = 0;
                            triangles[numTriangles].texCoords[i].x = 0;
                            triangles[numTriangles].texCoords[i].y = 0;
                    }
                    numTriangles++;

            }
            else
            {
            }
    }
    */
    else if (command == "quit") {
// This needs to be abstracted somehow
#ifdef WIN32
      PostQuitMessage(0);
#endif

    } else {
      ConsolePrint("Unknown command " + command);
    }
  }
}

void Level::ParseCmds(const char* lpCmdLine) {
  string cmd = lpCmdLine;
  string command;

  uint32_t i = 0;
  command = word(cmd, i);
  while (command != "") {
    if (command == "+set") {
      command = tolower(word(cmd, ++i));

      if (command == "turnspeed") {
        turnSpeed = (float)atof(word(cmd, ++i).c_str());
      } else if (command == "mousespeed") {
        mouseSpeed = (float)atof(word(cmd, ++i).c_str());
      } else if (command == "maxfps") {
        maxFPS = Integer(word(cmd, ++i));
      } else if (command == "sound") {
        sound = Truth(word(cmd, ++i));
      } else if (command == "game") {
        gamedir = word(cmd, ++i);
        if (gamedir[gamedir.length() - 1] != '/') {
          gamedir = gamedir + '/';
        }
      }
    } else if (command == "+bind") {
      command = tolower(word(cmd, ++i));

      if (command == "forward") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_FORWARD);
      } else if (command == "backward") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_BACKWARD);
      } else if (command == "lookleft") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_LOOKLEFT);
      } else if (command == "lookright") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_LOOKRIGHT);
      } else if (command == "lookup") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_LOOKUP);
      } else if (command == "lookdown") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_LOOKDOWN);
      } else if (command == "moveup") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_MOVEUP);
      } else if (command == "movedown") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_MOVEDOWN);
      } else if (command == "moveleft") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_MOVELEFT);
      } else if (command == "moveright") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_MOVERIGHT);
      } else if (command == "fireprimary") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_FIREPRIMARY);
      } else if (command == "firesecondary") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_FIRESECONDARY);
      } else if (command == "weapnext") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_WEAPONNEXT);
      } else if (command == "weapprev") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_WEAPONPREV);
      } else if (command == "togglelights" || command == "togglelighting") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_TOGGLE_LIGHTS);
      } else if (command == "togglefps") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_TOGGLE_FPS);
      } else if (command == "toggleconsole") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_TOGGLE_CONSOLE);
      } else if (command == "togglemouselook") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()),
                                       OpenArena::ControlScheme::ACTION_TOGGLE_MOUSELOOK);
      } else if (command == "quickmouselook") {
        defaultPlayer[0].controls.Bind(GetKey(word(cmd, ++i).c_str()), OpenArena::ControlScheme::ACTION_QUICKMOUSELOOK);
      }
    } else if (command == "+map" || command == "+map_load") {
      nextLevel = word(cmd, ++i);
      UnloadMap();
      LoadMap();
    } else if (command == "+unbind") {
      command = tolower(word(cmd, ++i));

      if (command == "all") {
        defaultPlayer[0].controls.UnBindAll();
      } else {
        defaultPlayer[0].controls.UnBind(GetKey(command.c_str()));
      }
    } else if (command == "+exec" || command == "+config_load") {
      command = tolower(word(cmd, ++i));
      LoadConfig(command);
    } else if (command == "+map_save") {
      command = tolower(word(cmd, ++i));
      SaveMap(command);
    } else if (command == "+config_save") {
      command = tolower(word(cmd, ++i));
      SaveConfig(command);
    }

    command = word(cmd, ++i);
  }
}

void Level::LoadConfig() {
  showFPS = false;
  nextLevel = "intro.map";
  gamedir = "oa/";
  sound = true;

  mouseSpeed = 5;
  turnSpeed = 1.0f;
  moveSpeed = .2f;
  mlook = true;
}

bool Level::LoadConfig(string cfgname) {
  ifstream input;
  string readBuffer;
  cfgname = gamedir + "config/" + cfgname;

  if (tolower(Right(cfgname, 4)) != ".cfg") cfgname = cfgname + ".cfg";

  input.open(cfgname.c_str());

  if (!input) return false;

  getline(input, readBuffer);

  while (input) {
    if (readBuffer[0] == '/' && readBuffer[1] == '/') {
      getline(input, readBuffer);
    }

    Execute(readBuffer);

    getline(input, readBuffer);
  }

  return true;
}

void Level::SaveConfig(string cfgname) {
  ofstream output;

  cfgname = gamedir + "config/" + cfgname;

  if (tolower(Right(cfgname, 4)) != ".cfg") cfgname = cfgname + ".cfg";

  output.open(cfgname.c_str());

  if (!output) return;

  // Client Config
  output << "set turnspeed " << turnSpeed << endl;
  output << "set mousespeed " << mouseSpeed << endl;
  output << "set mouselook " << mlook << endl;
  output << "set screenwidth " << screen.GetWidth() << endl;
  output << "set screenheight " << screen.GetHeight() << endl;
  output << "set colordepth " << screen.GetColorDepth() << endl;
  output << "set fullscreen " << screen.GetFullscreen() << endl;
  output << "set maxfps " << maxFPS << endl;

  // Control Scheme
  defaultPlayer->controls.WriteToStream(output);
}

void Level::Print(int x, int y, const char* str, unsigned int set) {
  glFont.Print(x, y, str, set);
}

void Level::UpdateConsole(char newChar) {
  if (newChar == '\n') {
    for (int i = MAX_CONSOLE_HISTORY_LINES - 1; i > 0; i--) {
      consoleHistory[i] = consoleHistory[i - 1];
    }
    consoleHistory[0] = "";
    ConsolePrint(consoleHistory[1]);
    Execute(tolower(consoleHistory[1]));

  } else if (newChar == OpenArena::KEY_BACK) {
    consoleHistory[0] = Left(consoleHistory[0], consoleHistory[0].length() - 1);
  } else if (!(defaultPlayer->controls.IsBound(GetKey(&newChar), ControlScheme::ACTION_TOGGLE_CONSOLE))) {
    consoleHistory[0] = consoleHistory[0] + newChar;
    /*
    char errmsg[256];
    sprintf(errmsg, "Unhangled keypress: %d", newChar);
    MessageBox(NULL, errmsg, "Balls", MB_OK);
    */
  }
}

void Level::ConsolePrint(string line) {
  for (int i = MAX_CONSOLE_OUTPUT_LINES - 1; i > 0; i--) {
    consoleOutput[i] = consoleOutput[i - 1];
  }
  consoleOutput[0] = line;
  Logger::LogInfo("Console Message: " + line);
}

void Level::SetWindow(Window* window) {
  _window = window;
}

Window* Level::GetWindow() {
  return _window;
}
}  // End namespace OpenArena
