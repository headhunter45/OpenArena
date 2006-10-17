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
////////////////////////////////////////////////////////////////////////////////
//
//	Module:		x11.cpp
//	Author:		Tom Hicks
//	Creation:	10-08-2006
//	LastEdit:	10-08-2006
//	Editors:	Tom Hicks
//
//	Purpose:
//		To implement the OpenArena SDK.
//
//	Summary of Methods:
//	Global
//		-InitControls()
//			Loads the defaultPlayer's configuration.
//		-InitGL()
//			Initializes OpenGL and is responsible for loading textures.
//		-ResizeGLScene(GLsizei width, GLsizei height)
//			Resizes the viewport to the current size of the visible area of the window specified by width and height.
//		-KillGLWindow()
//			Closes the window.
//		-CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag)
//			Creates the window with the specified parameters.
//		-WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//			Main procedure.
//		-WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//			Window Procedure for the OpenGL window.
//
////////////////////////////////////////////////////////////////////////////////
#include "x11.h"
#if defined USE_GLX
#include "main.h"
#include "version.h"

int InitGL(OpenArena::Level* level)
{
	level->LoadGLTextures();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/*lighting disabled temporarily
	glLightfv(GL_LIGHT1, GL_AMBIENT, level->LightAmbient);
	for(index=0; index<level->numLights; index++)
	{
	glLightfv(GL_LIGHT1, GL_DIFFUSE, level->light[index].color);
	glLightfv(GL_LIGHT1, GL_POSITION, level->light[index].coords);
	}

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	*/
	//BuildFont();
	return true;
}

//This should probably be moved into oa_input
OpenArena::Keys TranslateKey(int keyCode)
{
	switch (keyCode)
	{
	case XK_BackSpace:
		return OpenArena::KEY_BACK;
	case XK_Tab:
		return OpenArena::KEY_TAB;
	case XK_Return:
		return OpenArena::KEY_RETURN;
	case XK_Escape:
		return OpenArena::KEY_ESCAPE;
	case XK_Left:
		return OpenArena::KEY_LEFT;
	case XK_Right:
		return OpenArena::KEY_RIGHT;
	case XK_Up:
		return OpenArena::KEY_UP;
	case XK_Down:
		return OpenArena::KEY_DOWN;
	case XK_Home:
		return OpenArena::KEY_HOME;
	case XK_End:
		return OpenArena::KEY_END;
	case XK_Prior:
		return OpenArena::KEY_PRIOR;
	case XK_Next:
		return OpenArena::KEY_NEXT;
	case XK_Num_Lock:
		return OpenArena::KEY_NUMLOCK;
	case XK_KP_Enter:
		return OpenArena::KEY_RETURN;
	case XK_KP_Home:
		return OpenArena::KEY_HOME;
	case XK_KP_End:
		return OpenArena::KEY_END;
	case XK_KP_Prior:
		return OpenArena::KEY_PRIOR;
	case XK_KP_Next:
		return OpenArena::KEY_NEXT;
	case XK_KP_0:
		return OpenArena::KEY_NUMPAD0;
	case XK_KP_1:
		return OpenArena::KEY_NUMPAD1;
	case XK_KP_2:
		return OpenArena::KEY_NUMPAD2;
	case XK_KP_3:
		return OpenArena::KEY_NUMPAD3;
	case XK_KP_4:
		return OpenArena::KEY_NUMPAD4;
	case XK_KP_5:
		return OpenArena::KEY_NUMPAD5;
	case XK_KP_6:
		return OpenArena::KEY_NUMPAD6;
	case XK_KP_7:
		return OpenArena::KEY_NUMPAD7;
	case XK_KP_8:
		return OpenArena::KEY_NUMPAD8;
	case XK_KP_9:
		return OpenArena::KEY_NUMPAD9;
	case XK_KP_Multiply:
		return OpenArena::KEY_MULTIPLY;
	case XK_KP_Add:
		return OpenArena::KEY_ADD;
	case XK_KP_Subtract:
		return OpenArena::KEY_SUBTRACT;
	case XK_KP_Divide:
		return OpenArena::KEY_DIVIDE;
	case XK_F1:
		return OpenArena::KEY_F1;
	case XK_F2:
		return OpenArena::KEY_F2;
	case XK_F3:
		return OpenArena::KEY_F3;
	case XK_F4:
		return OpenArena::KEY_F4;
	case XK_F5:
		return OpenArena::KEY_F5;
	case XK_F6:
		return OpenArena::KEY_F6;
	case XK_F7:
		return OpenArena::KEY_F7;
	case XK_F8:
		return OpenArena::KEY_F8;
	case XK_F9:
		return OpenArena::KEY_F9;
	case XK_F10:
		return OpenArena::KEY_F10;
	case XK_F11:
		return OpenArena::KEY_F11;
	case XK_F12:
		return OpenArena::KEY_F12;
	case XK_Shift_L:
		return OpenArena::KEY_SHIFT;
	case XK_Shift_R:
		return OpenArena::KEY_SHIFT;
	case XK_Control_L:
		return OpenArena::KEY_CONTROL;
	case XK_Control_R:
		return OpenArena::KEY_CONTROL;
	case XK_Caps_Lock:
		return OpenArena::KEY_CAPITAL;
	case XK_Pause:
		return OpenArena::KEY_PAUSE;
	case XK_KP_Space:
	case XK_space:
		return OpenArena::KEY_SPACE;
	case XK_Insert:
		return OpenArena::KEY_INSERT;
	case XK_Delete:
		return OpenArena::KEY_DELETE;
	case XK_KP_Separator:
		return OpenArena::KEY_SEPARATOR;
	case XK_Scroll_Lock:
		return OpenArena::KEY_SCROLL;
	case XK_period:
		return OpenArena::KEY_OEM_PERIOD;
	case XK_plus:
		return OpenArena::KEY_OEM_PLUS;
	case XK_minus:
		return OpenArena::KEY_OEM_MINUS;
	case XK_comma:
		return OpenArena::KEY_OEM_COMMA;
	case XK_0:
		return OpenArena::KEY_0;
	case XK_1:
		return OpenArena::KEY_1;
	case XK_2:
		return OpenArena::KEY_2;
	case XK_3:
		return OpenArena::KEY_3;
	case XK_4:
		return OpenArena::KEY_4;
	case XK_5:
		return OpenArena::KEY_5;
	case XK_6:
		return OpenArena::KEY_6;
	case XK_7:
		return OpenArena::KEY_7;
	case XK_8:
		return OpenArena::KEY_8;
	case XK_9:
		return OpenArena::KEY_9;
	case XK_a:
	case XK_A:
		return OpenArena::KEY_A;
	case XK_b:
	case XK_B:
		return OpenArena::KEY_B;
	case XK_c:
	case XK_C:
		return OpenArena::KEY_C;
	case XK_d:
	case XK_D:
		return OpenArena::KEY_D;
	case XK_e:
	case XK_E:
		return OpenArena::KEY_E;
	case XK_f:
	case XK_F:
		return OpenArena::KEY_F;
	case XK_g:
	case XK_G:
		return OpenArena::KEY_G;
	case XK_h:
	case XK_H:
		return OpenArena::KEY_H;
	case XK_i:
	case XK_I:
		return OpenArena::KEY_I;
	case XK_j:
	case XK_J:
		return OpenArena::KEY_J;
	case XK_k:
	case XK_K:
		return OpenArena::KEY_K;
	case XK_l:
	case XK_L:
		return OpenArena::KEY_L;
	case XK_m:
	case XK_M:
		return OpenArena::KEY_M;
	case XK_n:
	case XK_N:
		return OpenArena::KEY_N;
	case XK_o:
	case XK_O:
		return OpenArena::KEY_O;
	case XK_p:
	case XK_P:
		return OpenArena::KEY_P;
	case XK_q:
	case XK_Q:
		return OpenArena::KEY_Q;
	case XK_r:
	case XK_R:
		return OpenArena::KEY_R;
	case XK_s:
	case XK_S:
		return OpenArena::KEY_S;
	case XK_t:
	case XK_T:
		return OpenArena::KEY_T;
	case XK_u:
	case XK_U:
		return OpenArena::KEY_U;
	case XK_v:
	case XK_V:
		return OpenArena::KEY_V;
	case XK_w:
	case XK_W:
		return OpenArena::KEY_W;
	case XK_x:
	case XK_X:
		return OpenArena::KEY_X;
	case XK_y:
	case XK_Y:
		return OpenArena::KEY_Y;
	case XK_z:
	case XK_Z:
		return OpenArena::KEY_Z;
	case XK_grave:
		return OpenArena::KEY_OEM_3;
	case XK_Super_L:
		return OpenArena::KEY_LWIN;
	case XK_Super_R:
		return OpenArena::KEY_RWIN;
	case XK_Menu:
		return OpenArena::KEY_APPS;
	case XK_bracketleft:
		return OpenArena::KEY_OEM_4;
	case XK_bracketright:
		return OpenArena::KEY_OEM_6;
	case XK_backslash:
		return OpenArena::KEY_OEM_5;
	case XK_semicolon:
		return OpenArena::KEY_OEM_1;
	case XK_apostrophe:
		return OpenArena::KEY_OEM_7;
	case XK_slash:
		return OpenArena::KEY_OEM_2;
	case XK_Alt_L:
		return OpenArena::KEY_ALT_L;
	case XK_Alt_R:
		return OpenArena::KEY_ALT_L;
	case XK_equal:
		return OpenArena::KEY_OEM_PLUS;
	case XK_Mode_switch:
		return OpenArena::KEY_OPTION;
	case XK_Meta_L:
		return OpenArena::KEY_COMMAND;
	case 16777219:
		return OpenArena::KEY_ENTER;
	default:
		return OpenArena::KEY_UNKNOWN;
	}
}

OpenArena::Keys TranslateButton(int keyCode)
{
	switch(keyCode)
	{
		case Button1:
			return OpenArena::KEY_BUTTON0;
		case Button2:
			return OpenArena::KEY_BUTTON2;
		case Button3:
			return OpenArena::KEY_BUTTON1;
		case Button4:
			return OpenArena::KEY_BUTTON3;
		case Button5:
			return OpenArena::KEY_BUTTON4;
	}
}

void HandleConsoleKeyPress(OpenArena::Keys key, OpenArena::Level* level)
{
	if(level->defaultPlayer[0].controls.IsBound(key, OpenArena::ControlScheme::ACTION_TOGGLE_CONSOLE))
	{
		level->showConsole = false;
	}

	switch (key)
	{
	case OpenArena::KEY_SHIFT:
		keys[OpenArena::KEY_SHIFT] = true;
		break;
	case OpenArena::KEY_RETURN:
		level->UpdateConsole('\n');
		break;
	case OpenArena::KEY_SPACE:
		printf("hello");
		level->UpdateConsole(' ');
		break;
	case OpenArena::KEY_BACK:
		level->UpdateConsole(OpenArena::KEY_BACK);
		break;
	case OpenArena::KEY_ESCAPE:
		level->showConsole = false;
		break;
	default:
		char ascii = OpenArena::KeyToASCII(key, keys[OpenArena::KEY_SHIFT]);
		if(ascii != '\0')
		{
			level->UpdateConsole(ascii);
		}
	}
}

void ResizeGLScene(GLsizei width, GLsizei height)
{
	if(height == 0)
		height = 1;

	glViewport(0,0,width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width/height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void RT()
{
}

#endif /* USE_GLX */
