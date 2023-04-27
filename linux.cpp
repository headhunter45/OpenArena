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
#ifdef __linux

// include necessary header files
#include "main.h"
#include "version.h"
#include "x11.h"
using namespace std;

void InitControls();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions

int DrawGLScene(OpenArena::Level* level) {
  level->Render();

  g_Screen->SwapBuffers();

  return true;
}

//
// void InitControls()
//  Purpose:
//	    Initializes controls by loading the default control config file "my.cfg".
void InitControls(OpenArena::Level* level) {
  if (!level->LoadConfig("my.cfg")) level->LoadConfig();
}

int main(int argc, char** argv) {
  OpenArena::EventManager* em = new OpenArena::EventManager();
  OpenArena::Level* level = new OpenArena::Level(em);
  XEvent event;
  bool done = false;

  string commandLine = "";
  int i;
  for (i = 1; i < argc; i++) {
    commandLine = commandLine + " " + argv[i];
  }
  level->ParseCmds(commandLine.c_str());

  InitControls(level);

  level->glFont.SetScreenDimensions(level->screen.GetWidth() * 2, level->screen.GetHeight() * 2);

  // Hack for now
  if (level->screen.GetColorDepth() == 32) {
    level->screen.SetColorDepth(24);
  }

  //	g_Screen.SetOnInit(InitGL);
  //	g_Screen.SetOnResize(ResizeGLScene);

  if (!g_Screen->Open(OPENARENA_VERSION,
                      level->screen.GetWidth(),
                      level->screen.GetHeight(),
                      level->screen.GetColorDepth(),
                      level->screen.GetFullscreen())) {
    return 1;
  }

  level->SetWindow(g_Screen);

  if (level->nextLevel == "") {
    level->LoadMap("intro.map");
  } else {
    level->LoadMap();
  }

  while (!done) {
    while (XPending(g_Screen->GetDisplay()) > 0) {
      // Equivalent of WNDPROC
      XNextEvent(g_Screen->GetDisplay(), &event);
      switch (event.type) {
        case Expose:
          if (event.xexpose.count != 0) {
            break;
          }
          DrawGLScene(level);
          break;
        case ConfigureNotify:
          if ((event.xconfigure.width != g_Screen->GetWidth()) || (event.xconfigure.height != g_Screen->GetHeight())) {
            g_Screen->SetWidth(event.xconfigure.width);
            g_Screen->SetHeight(event.xconfigure.height);
            ResizeGLScene(event.xconfigure.width, event.xconfigure.height);
          }
          break;
        case ButtonPress:
          keys[TranslateButton(event.xbutton.button)] = true;
          break;
        case ButtonRelease:
          keys[TranslateButton(event.xbutton.button)] = false;
          keys2[TranslateButton(event.xbutton.button)] = false;
          break;
        case KeyPress:
          if (level->showConsole) {
            HandleConsoleKeyPress((OpenArena::Keys)TranslateKey(XLookupKeysym(&event.xkey, 0)), level);
          } else {
            keys[TranslateKey(XLookupKeysym(&event.xkey, 0))] = true;
          }
          break;
        case KeyRelease:
          keys[TranslateKey(XLookupKeysym(&event.xkey, 0))] = false;
          keys2[TranslateKey(XLookupKeysym(&event.xkey, 0))] = false;
          break;
        case ClientMessage:
          if (*XGetAtomName(g_Screen->GetDisplay(), event.xclient.message_type) == *"WM_PROTOCOLS") {
            printf("Exiting sanely...\n");
            done = true;
          }
          break;
        default:
          break;
      }
    }  // End Equivalent of WNDPROC

    if (active) {
      if (keys[OpenArena::KEY_ESCAPE]) {
        done = true;
      } else if (keys[OpenArena::KEY_F1]) {
        g_Screen->Close();
        g_Screen->ToggleFullscreen();
        g_Screen->Open();
      } else {
        level->defaultPlayer[0].camera.Update();
        if (!level->showConsole) {
          if (level->mlook) {
            using OpenArena::Vec2i;
            Vec2i middleOfScreen = Vec2i(g_Screen->GetWidth() / 2, g_Screen->GetHeight() / 2);
            Vec2i mousePosition = g_Screen->GetMousePosition();
            if (mousePosition != middleOfScreen) {
              // Vec2i mouseDelta = mousePosition - middleOfScreen;
              Vec2i mouseDelta = middleOfScreen - mousePosition;
              g_Screen->SetMousePosition(middleOfScreen);
              const float MOUSE_SENSITIVITY_HORIZONTAL = 0.005;
              const float MOUSE_SENSITIVITY_VERTICAL = 0.005;
              float horizontalAngle = mouseDelta.x * MOUSE_SENSITIVITY_HORIZONTAL;
              float verticalAngle = mouseDelta.y * MOUSE_SENSITIVITY_VERTICAL;
              level->defaultPlayer[0].camera.RotateHorizontal(horizontalAngle);
              level->defaultPlayer[0].camera.RotateVertical(verticalAngle);
            }
          } else {
#ifdef WIN32
            SetCursorPos(g_Screen->width / 2, g_Screen->height / 2);  // Shit this may be windows specific
#endif
          }
        }
      }
    }

    DrawGLScene(level);

    if (keys[OpenArena::KEY_F1]) {
      keys[OpenArena::KEY_F1] = false;
      g_Screen->Close();
      g_Screen->ToggleFullscreen();
      if (!g_Screen->Open(OPENARENA_VERSION,
                          level->screen.GetWidth(),
                          level->screen.GetHeight(),
                          level->screen.GetColorDepth(),
                          level->screen.GetFullscreen())) {
        return 1;
      }
    }
  }
  level->UnloadMap();
  g_Screen->Close();
  exit(0);
}

bool keys[256];
bool keys2[256];
bool active;
bool fullscreen;
// bool           showConsole = false;
OpenArena::Vec2i g_mousePosition;
float lastTime;
float currentTime;

#endif
