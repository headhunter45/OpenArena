////////////////////////////////////////////////////////////////////////////////
//
//	Module:		level.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	06-20-2005
//	Editors:	Tom Hicks
//
//	Purpose:
//		To implement the world or at least a reasonable copy.
//
//	Summary of Methods:
//	Global
//		-function name
//			description
//	blahClass
//		-function name
//			description
//
//	Summary of Properties:
//	blahClass
//		-property name
//			description
//
////////////////////////////////////////////////////////////////////////////////

#include "level.h"
#include "version.h"

#pragma comment(lib, "bass.lib")
#ifdef WIN32
#pragma warning(disable:4996)
#endif
using namespace std;

namespace OpenArena
{
	Level::Level()
	{
		_window = NULL;
		textureNames = NULL;
		numTextures = 0;
	
		screen.SetName(OPENARENA_VERSION);
	
		showFPS = false;
		showConsole = false;
	
		nextLevel = "intro.map";
			gamedir = "oa/";
		sound = true;
	
		defaultPlayer = new Player;
	
		numTriangles = 0;
		triangles = NULL;
		/*
		for(int x=0; x<4; x++)
		LightAmbient[x] = 5;
		*/
		//Player Stuff
		mouseSpeed = 5;
		turnSpeed = 1.0f;
		moveSpeed = 0.2f;
		mlook = true;
	}
	
	Level::~Level()
	{
		if(defaultPlayer)
		{
			delete defaultPlayer;
			defaultPlayer = NULL;
		}
	}
	
	bool Level::LoadMap(string mapname)
	{
		ifstream input;
		string readBuffer;
	
		//players.Insert(*defaultPlayer);
	
		mapname = gamedir + "maps/" + mapname;
	
		if(tolower(Right(mapname, 4)) != ".map")
			mapname = mapname + ".map";
	
		input.open(mapname.c_str());
	
		if(!input)
		{
			char* tmpChar = new char[mapname.length() + 41];
			strcpy(tmpChar, "Unable to load level file ");
			strcat(tmpChar, mapname.c_str());
			strcat(tmpChar, " doesn't exist.");
			
			//This needs to be abstracted somehow
			#ifdef WIN32
			MessageBox(NULL,tmpChar,"ERROR",MB_OK|MB_ICONEXCLAMATION);
			#endif
			delete [] tmpChar;
			return false;
		}
		else
		{
			ConsolePrint("map file \"" + mapname + "\" opened successfully");
		}
	
		//Gravity
		input >> readBuffer;
		gravity = (float)atof(readBuffer.c_str());
	
		//Number of triangles
		input >> readBuffer;
		numTriangles = Integer(readBuffer);
	
		//Triangle Data
		triangles = new Triangle[numTriangles];
		for(unsigned int i=0; i<numTriangles; i++)
		{
			//TextureID
			input >> readBuffer;
			triangles[i].texID = Integer(readBuffer);
	
			for(unsigned int i2=0; i2<3; i2++)
			{
				//Vertex Data
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
	
			//Normal
			input >> readBuffer;
	
			triangles[i].normal.x = atof(readBuffer.c_str());
			input >> readBuffer;
			triangles[i].normal.y = atof(readBuffer.c_str());
			input >> readBuffer;
			triangles[i].normal.z = atof(readBuffer.c_str());
		}
		char lpszNumTriangles[6];
		sprintf(lpszNumTriangles, "%d", numTriangles);
		ConsolePrint(lpszNumTriangles + string(" triangles successfully read"));
	
		//Number of textures;
		input >> readBuffer;
		numTextures = Integer(readBuffer);
	
		//Texture data
		textureNames = new string[numTextures];
		for(unsigned int i=0; i<numTextures; i++)
		{
			input >> textureNames[i];	
		}
		LoadGLTextures();
		char lpszNumTextures[6];
		sprintf(lpszNumTextures, "%d", numTextures);
		ConsolePrint(lpszNumTextures + string(" textures successfully read"));
	
		//BGM
		input >> bgm;
	
		//Build display list
		
		//Sound
		if (sound)
		{
			ConsolePrint("Starting sound");
	
			//This needs to be abstracted somehow
			#ifdef WIN32
			BASS_Init(-1, 44100, BASS_DEVICE_LEAVEVOL, g_hWnd);
			BASS_Start();
			BASS_CDInit(NULL, BASS_DEVICE_LEAVEVOL);
			#endif
			
			if(bgm.length()>=4)
			{
				if( toupper(bgm[0]) == 'C' &&
					toupper(bgm[1]) == 'D' &&
					toupper(bgm[2]) == 'A')
				{
					bgmCDA = Integer(bgm.substr(3,bgm.length()));
					//This needs to be abstracted somehow
					#ifdef WIN32
					BASS_CDPlay(bgmCDA, 1, 0);
					#endif
				}
				else
				{
					bgmCDA=0;
					string tmpstr = gamedir + "music/bgm/" + bgm;
					//This needs to be abstracted somehow
					#ifdef WIN32
					bgmStream = BASS_StreamCreateFile(0, (void*)tmpstr.c_str(), 0, 0, BASS_STREAM_AUTOFREE);
					BASS_StreamPlay(bgmStream, 1, BASS_SAMPLE_LOOP);					
					#endif
				}
			}
	
			ConsolePrint("Sound init complete");
		}
		else
		{
			ConsolePrint("Sound disabled");
		}
	
		return true;
	}
	bool Level::LoadMap()
	{
		return LoadMap(nextLevel);
	}
	
	void Level::SaveMap(string mapname)
	{
		ofstream output;
		
		mapname = gamedir + "maps/" + mapname;
	
		if(tolower(Right(mapname, 4)) != ".map")
			mapname = mapname + ".map";
	
		output.open(mapname.c_str());
	
		if(!output)
		{
			char* tmpChar = new char[mapname.length() + 42];
			strcpy(tmpChar, "Unable to save level file ");
			strcat(tmpChar, mapname.c_str());
			strcat(tmpChar, " already exists.");
	
			//This needs to be abstracted somehow
			#ifdef WIN32
			MessageBox(NULL,tmpChar,"ERROR",MB_OK|MB_ICONEXCLAMATION);
			#endif
			delete [] tmpChar;
			return;
		}
	
		//Gravity
		output << gravity << endl;
	
		//Number of triangles
		output << numTriangles << endl;
		
		//Triangle Data
		for(unsigned int i=0; i<numTriangles; i++)
		{
			output << triangles[i].texID << endl;
	
			for(unsigned int i2=0; i2<3; i2++)
			{
				output << triangles[i].vertecies[i2].coordinates.x << " "
					   << triangles[i].vertecies[i2].coordinates.y << " "
					   << triangles[i].vertecies[i2].coordinates.z << " "
					   << triangles[i].vertecies[i2].textureCoordinates.x << " "
					   << triangles[i].vertecies[i2].textureCoordinates.y << endl;
			}
	
			output << triangles[i].normal.x << " "
				   << triangles[i].normal.y << " "
				   << triangles[i].normal.z << endl;
		}
	
		//Number of textures;
		output << numTextures;
	
		//Texture data
		for(unsigned int i=0; i<numTextures; i++)
		{
			output << textureNames[i];	
		}
	
		//BGM
		output << bgm;
	
	}
	
	void Level::Render()
	{
		glPushMatrix();	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	
		// Move the camera to where the player is
		defaultPlayer->camera.Look();
	
		for (uint32 i=0; i<numTriangles; i++)
		{
			glBindTexture(GL_TEXTURE_2D, textures[triangles[i].texID]->ID());//Bind this triangle's texture
			glBegin(GL_TRIANGLES);
	//		glNormal3f((GLfloat)triangles[i].normal.x, (GLfloat)triangles[i].normal.y, (GLfloat)triangles[i].normal.z);
			for (uint32 i2=0; i2<3; i2++)
			{
				glTexCoord2f(triangles[i].vertecies[i2].textureCoordinates.x,
							 triangles[i].vertecies[i2].textureCoordinates.y);
				glVertex3f((GLfloat)triangles[i].vertecies[i2].coordinates.x,
						   (GLfloat)triangles[i].vertecies[i2].coordinates.y,
						   (GLfloat)triangles[i].vertecies[i2].coordinates.z);
			}
			glEnd();
		}
		glPopMatrix();
	
		//Draw HUD
		//ummm nothing here yet
	
	
	
		//Draw FPS
		//This may not work yet
		if (showFPS)
		{
			char fps[20];
			sprintf(fps, "fps %d", FPS());
			glPushMatrix();
			glLoadIdentity();
			glColor3f(1,1,1);
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glFont.Print(glFont.ScreenWidth() - 120, glFont.ScreenHeight() - 30, fps, 0);
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glPopMatrix();
		}
	
		if(showConsole)
		{
			glPushMatrix();
			glLoadIdentity();
			glColor3f(1,1,1);
	
			//disable lighting and depth testing
			glDisable(GL_DEPTH_TEST);
	
			glBindTexture(GL_TEXTURE_2D, menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].ID());
			//glBindTexture(GL_TEXTURE_2D, 4);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, screen.GetWidth(), 0, screen.GetHeight(), -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
	
			
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2i(0,screen.GetHeight()/2);
				glTexCoord2f(0,1);
				glVertex2i(0,screen.GetHeight());
				glTexCoord2f(1,1);
				glVertex2i(screen.GetWidth(),screen.GetHeight());
				glTexCoord2f(1,0);
				glVertex2i(screen.GetWidth(),screen.GetHeight()/2);
			glEnd();
	
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
			
			glDisable(GL_LIGHTING);
	
			//enable blending
			glEnable(GL_BLEND);
	
			//render the console background
			//render the console output text
			unsigned int i;
			for(i=0; i<MAX_CONSOLE_LINES-1; i++)
			{
				Print(30, glFont.ScreenHeight() - i*20, consoleOutput[MAX_CONSOLE_LINES-i-2].c_str(), 0);
			}
	
			//Render the currently typed command
			Print(30,glFont.ScreenHeight() - i*20, consoleHistory[0].c_str(),0);
	
			//disable blending
			glDisable(GL_BLEND);
	
			//re-enable lighting and depth testing
			//glEnable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);
		}
	}
	
	void Level::UnloadMap()
	{
		//Stop audio
		//This needs to be abstracted somehow
		#ifdef WIN32
		BASS_StreamFree(bgmStream);
		BASS_Stop();
		BASS_CDFree();
		BASS_Free();
		#endif
		
		//Delete display list
		
		//Free all polygon data
		if(triangles)
		{
			delete [] triangles;
			triangles = NULL;
		}
		
		//Free all map textures
		if(!textures.IsEmpty())
		{
			//TODOiterate over list and delete all entries
		}
		textures.Clear();
	
		//Free the array of texture names
		if (textureNames)
		{
			delete [] textureNames;
			textureNames = NULL;
		}
	}
	
	void Level::LoadGLTextures()
	{
		if(_window != NULL)
		{
			/*
			GLfloat light[4] = {1.0f,1.0f,1.0f,0.5f};
			glLightfv(GL_LIGHT1, GL_AMBIENT, light);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHTING);
			*/
		
			textures.Clear();		
		
			for(uint32 i=0; i<numTextures; i++)
			{
				Texture* texture = new Texture();
				if(!texture->Load(gamedir + "textures/" + textureNames[i]))
					texture->Load(DEFAULT_TEXTURE_NAME);
				textures[i] = texture;
			}
		
			if(!glFont.BuildFont((gamedir + "textures/menu/font.bmp").c_str()))
				glFont.BuildFont("oa/textures/menu/font.bmp");
	
			//Load the console background image
			if(!menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].Load(gamedir + "textures/menu/con_back.tga"))
			{
				menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].Load("oa/textures/menu/con_back.bmp");
			}
		}
	}
	
	uint32 Level::FPS()
	{
		static uint32 fps=0;
		static uint32 fps2=0;
		static float last=0.0f;  // might need to change to double
	
		//hmmm what the hell is this called in linux I should possibly abstract this
		#ifdef WIN32
		float time=GetTickCount()*.001f;
		#else
		float time = 0;
		#endif
	
		++fps;
	
		if(time>last+1)
		{
			last=time;
			fps2 = fps;
			fps=0;
		}
		return fps2;
	}
	
	void Level::Execute(string cmd)
	{
		string command;
		
		uint32 i=0xFFFFFFFF;
		while(word(cmd, ++i) != "")
		{
			command = tolower(word(cmd, i));
			
			if(command == "set")
			{
				command = tolower(word(cmd, ++i));
				
				if(command == "turnspeed")
				{
					turnSpeed = (float)atof(word(cmd, ++i).c_str());//Floating(word(cmd, ++i));
				}
				else if(command == "movespeed")
				{
					moveSpeed = (float)atof(word(cmd, ++i).c_str());//FLoating(word(cmd, ++i));
				}
				else if(command == "mousespeed")
				{
					mouseSpeed = (float)atof(word(cmd, ++i).c_str());
				}
				else if(command == "mouselook")
				{
					mlook = Truth(word(cmd, ++i));
				}
				else if(command == "maxfps")
				{
					maxFPS = Integer(word(cmd, ++i));
				}
				else if(command == "sound")
				{
					sound = Truth(word(cmd, ++i));
				}
				else if(command == "game")
				{
					gamedir= word(cmd, ++i);
				}
				else if(command == "screenwidth")
				{
					screen.SetWidth(Integer(word(cmd, ++i)));
				}
				else if(command == "screenheight")
				{
					screen.SetHeight(Integer(word(cmd, ++i)));
				}
				else if(command == "fullscreen")
				{
					screen.SetFullscreen(Truth(word(cmd, ++i)));
				}
				else if(command == "colordepth")
				{
					screen.SetColorDepth(Integer(word(cmd, ++i)));
				}
				else
				{
					ConsolePrint("Variable " + command + " doesn't exist");
				}
			}
			else if(command == "bind")
			{
				command = tolower(word(cmd, ++i));
	
				if(command == "forward")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_FORWARD, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action forward");
					}
				}
				else if(command == "backward")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_BACKWARD, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action backward");
					}
				}
				else if(command == "lookleft")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKLEFT, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action lookleft");
					}
				}
				else if(command == "lookright")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKRIGHT, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action lookright");
					}
				}
				else if(command == "lookup")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKUP, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action lookup");
					}
				}
				else if(command == "lookdown")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKDOWN, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action lookdown");
					}
				}
				else if(command == "moveup")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVEUP, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action moveup");
					}
				}
				else if(command == "movedown")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVEDOWN, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action movedown");
					}
				}
				else if(command == "moveleft")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVELEFT, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action moveleft");
					}
				}
				else if(command == "moveright")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVERIGHT, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action moveright");
					}
				}
				else if(command == "fireprimary")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_FIREPRIMARY, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action fireprimary");
					}
				}
				else if(command == "firesecondary")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_FIRESECONDARY, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action firesecondary");
					}
				}
				else if(command == "weapnext")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_WEAPONNEXT, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action weapnext");
					}
				}
				else if(command == "weapprev")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_WEAPONPREV, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action weapprev");
					}
				}
				else if(command == "togglelights" || command == "togglelighting")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_LIGHTS, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action togglelights");
					}
				}
				else if(command == "togglefps")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_FPS, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action togglefps");
					}
				}
				else if(command == "toggleconsole")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_CONSOLE, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action toggleconsole");
					}
				}
				else if(command == "togglemouselook")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_MOUSELOOK, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action togglemouselook");
					}
				}
				else if(command == "quickmouselook")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_QUICKMOUSELOOK, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action quickmouselook");
					}
				}
				else if(command == "rollleft")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_ROLLLEFT, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action rollleft");
					}
				}
				else if(command == "rollright")
				{
					if(!defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_ROLLRIGHT, KeyName(word(cmd, ++i))))
					{
						ConsolePrint("Couldn't bind " + word(cmd, i) + " to action rollright");
					}
				}
				else
				{
					ConsolePrint("No action identified by " + command);
				}
			}
			else if(command == "map" || command == "map_load")
			{
				nextLevel = word(cmd, ++i);
				UnloadMap();
				if(!LoadMap())
				{
					ConsolePrint("Unable to load level " + command);
					nextLevel = "intro.map";
					LoadMap();
				}
			}
			else if(command == "unbind")
			{
				command = tolower(word(cmd, ++i));
				
				if(command == "all")
				{
					defaultPlayer[0].controls.ClearControlScheme();
				}
				else
				{
					defaultPlayer[0].controls.Unbind(KeyName(command));
				}
			}
			else if(command == "exec" || command == "config_load")
			{
				command = tolower(word(cmd, ++i));
				if(!LoadConfig(command))
				{
					ConsolePrint("Unable to load config file " + word(cmd, i));
				}
			}
			else if(command == "map_save")
			{
				command = tolower(word(cmd, ++i));
				SaveMap(command);
			}
			else if(command == "config_save")
			{
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
			else if(command == "quit")
			{
				//This needs to be abstracted somehow
				#ifdef WIN32
				PostQuitMessage(0);
				#endif
				
			}
			else
			{
				ConsolePrint("Unknown command " + command);
			}
		}
	}
	
	void Level::ParseCmds(const char* lpCmdLine)
	{
		string cmd = lpCmdLine;
		string command;
		
		uint32 i=0xFFFFFFFF;
		while(word(cmd, ++i) != "")
		{
			command = word(cmd, i);
			
			if(command == "+set")
			{
				command = tolower(word(cmd, ++i));
				
				if(command == "turnspeed")
				{
					turnSpeed = (float)atof(word(cmd, ++i).c_str());
				}
				else if(command == "mousespeed")
				{
					mouseSpeed = (float)atof(word(cmd, ++i).c_str());
				}
				else if(command == "maxfps")
				{
					maxFPS = Integer(word(cmd, ++i));
				}
				else if(command == "sound")
				{
					sound = Truth(word(cmd, ++i));
				}
				else if(command == "game")
				{
					gamedir= word(cmd, ++i);
				}
			}
			else if(command == "+bind")
			{
				command = tolower(word(cmd, ++i));
	
				if(command == "forward")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_FORWARD, KeyName(word(cmd, ++i)));
				}
				else if(command == "backward")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_BACKWARD, KeyName(word(cmd, ++i)));
				}
				else if(command == "lookleft")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKLEFT, KeyName(word(cmd, ++i)));
				}
				else if(command == "lookright")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKRIGHT, KeyName(word(cmd, ++i)));
				}
				else if(command == "lookup")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKUP, KeyName(word(cmd, ++i)));
				}
				else if(command == "lookdown")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_LOOKDOWN, KeyName(word(cmd, ++i)));
				}
				else if(command == "moveup")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVEUP, KeyName(word(cmd, ++i)));
				}
				else if(command == "movedown")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVEDOWN, KeyName(word(cmd, ++i)));
				}
				else if(command == "moveleft")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVELEFT, KeyName(word(cmd, ++i)));
				}
				else if(command == "moveright")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_MOVERIGHT, KeyName(word(cmd, ++i)));
				}
				else if(command == "fireprimary")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_FIREPRIMARY, KeyName(word(cmd, ++i)));
				}
				else if(command == "firesecondary")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_FIRESECONDARY, KeyName(word(cmd, ++i)));
				}
				else if(command == "weapnext")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_WEAPONNEXT, KeyName(word(cmd, ++i)));
				}
				else if(command == "weapprev")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_WEAPONPREV, KeyName(word(cmd, ++i)));
				}
				else if(command == "togglelights" || command == "togglelighting")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_LIGHTS, KeyName(word(cmd, ++i)));
				}
				else if(command == "togglefps")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_FPS, KeyName(word(cmd, ++i)));
				}
				else if(command == "toggleconsole")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_CONSOLE, KeyName(word(cmd, ++i)));
				}
				else if(command == "togglemouselook")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_TOGGLE_MOUSELOOK, KeyName(word(cmd, ++i)));
				}
				else if(command == "quickmouselook")
				{
					defaultPlayer[0].controls.Bind(OpenArena::ControlScheme::ACTION_QUICKMOUSELOOK, KeyName(word(cmd, ++i)));
				}
			}
			else if(command == "+map" || command == "+map_load")
			{
				nextLevel = word(cmd, ++i);
				UnloadMap();
				LoadMap();
			}
			else if(command == "+unbind")
			{
				command = tolower(word(cmd, ++i));
				
				if(command == "all")
				{
					defaultPlayer[0].controls.ClearControlScheme();
				}
				else
				{
					defaultPlayer[0].controls.Unbind(KeyName(command));
				}
			}
			else if(command == "+exec" || command == "+config_load")
			{
				command = tolower(word(cmd, ++i));
				LoadConfig(command);
			}
			else if(command == "+map_save")
			{
				command = tolower(word(cmd, ++i));
				SaveMap(command);
			}
			else if(command == "+config_save")
			{
				command = tolower(word(cmd, ++i));
				SaveConfig(command);
			}
			
		}
	}
	
	void Level::LoadConfig()
	{
		showFPS = false;
		nextLevel = "intro.map";
			gamedir = "oa/";
		sound = true;
	
		mouseSpeed = 5;
		turnSpeed = 1.0f;
		moveSpeed = .2f;
		mlook = true;
	}
	bool Level::LoadConfig(string cfgname)
	{
		ifstream input;
		string readBuffer;
	
		cfgname = gamedir + "config/" + cfgname;
	
		if(tolower(Right(cfgname, 4)) !=".cfg")
			cfgname = cfgname + ".cfg";
	
		input.open(cfgname.c_str());
	
		if(!input)
			return false;
	
		getline(input, readBuffer);
	
		while(input)
		{
			uint32 i=0xFFFFFFFF;
	
			if(readBuffer[0] == '/' && readBuffer[1] == '/')
			{
				getline(input, readBuffer);
			}
	
			Execute(readBuffer);
	
			getline(input, readBuffer);
		}
	
		return true;
	}
	
	void Level::SaveConfig(string cfgname)
	{
		ofstream output;
	
		cfgname = gamedir + "config/" + cfgname;
	
		if(tolower(Right(cfgname, 4)) !=".cfg")
			cfgname = cfgname + ".cfg";
	
		output.open(cfgname.c_str());
	
		if(!output)
			return;
	
		//Client Config
		output << "set turnspeed " << turnSpeed << endl;
		output << "set mousespeed " << mouseSpeed << endl;
		output << "set mouselook " << mlook << endl;
		output << "set screenwidth " << screen.GetWidth() << endl;
		output << "set screenheight " << screen.GetHeight() << endl;
		output << "set colordepth " << screen.GetColorDepth() << endl;
		output << "set fullscreen " << screen.GetFullscreen() << endl;
		output << "set maxfps " << maxFPS << endl;
	
		//Control Scheme
		//output << " bind " << action << keyname << endl;
		if(!defaultPlayer->controls.backward.IsEmpty())
		{
			defaultPlayer->controls.backward.FirstPosition();
			output << "bind backward " << string(KeyString(defaultPlayer->controls.backward.Retrieve())) << endl;
			while(defaultPlayer->controls.backward.NextPosition())
				output << "bind backward " << KeyString(defaultPlayer->controls.backward.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.firePrimary.IsEmpty())
		{
			defaultPlayer->controls.firePrimary.FirstPosition();
			output << "bind firePrimary " << KeyString(defaultPlayer->controls.firePrimary.Retrieve()) << endl;
			while(defaultPlayer->controls.firePrimary.NextPosition())
				output << "bind firePrimary " << KeyString(defaultPlayer->controls.firePrimary.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.fireSecondary.IsEmpty())
		{
			defaultPlayer->controls.fireSecondary.FirstPosition();
			output << "bind fireSecondary " << KeyString(defaultPlayer->controls.fireSecondary.Retrieve()) << endl;
			while(defaultPlayer->controls.fireSecondary.NextPosition())
				output << "bind fireSecondary " << KeyString(defaultPlayer->controls.fireSecondary.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.forward.IsEmpty())
		{
			defaultPlayer->controls.forward.FirstPosition();
			output << "bind forward " << KeyString(defaultPlayer->controls.forward.Retrieve()) << endl;
			while(defaultPlayer->controls.forward.NextPosition())
				output << "bind forward " << KeyString(defaultPlayer->controls.forward.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.lookDown.IsEmpty())
		{
			defaultPlayer->controls.lookDown.FirstPosition();
			output << "bind lookDown " << KeyString(defaultPlayer->controls.lookDown.Retrieve()) << endl;
			while(defaultPlayer->controls.lookDown.NextPosition())
				output << "bind lookDown " << KeyString(defaultPlayer->controls.lookDown.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.lookLeft.IsEmpty())
		{
			defaultPlayer->controls.lookLeft.FirstPosition();
			output << "bind lookLeft " << KeyString(defaultPlayer->controls.lookLeft.Retrieve()) << endl;
			while(defaultPlayer->controls.lookLeft.NextPosition())
				output << "bind lookLeft " << KeyString(defaultPlayer->controls.lookLeft.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.lookRight.IsEmpty())
		{
			defaultPlayer->controls.lookRight.FirstPosition();
			output << "bind lookRight " << KeyString(defaultPlayer->controls.lookRight.Retrieve()) << endl;
			while(defaultPlayer->controls.lookRight.NextPosition())
				output << "bind lookRight " << KeyString(defaultPlayer->controls.lookRight.Retrieve()) << endl;
		}
		if(!defaultPlayer->controls.lookUp.IsEmpty())
		{
			defaultPlayer->controls.lookUp.FirstPosition();
			output << "bind lookUp " << KeyString(defaultPlayer->controls.lookUp.Retrieve()) << endl;
			while(defaultPlayer->controls.lookUp.NextPosition())
				output << "bind lookUp " << KeyString(defaultPlayer->controls.lookUp.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.moveDown.IsEmpty())
		{
			defaultPlayer->controls.moveDown.FirstPosition();
			output << "bind moveDown " << KeyString(defaultPlayer->controls.moveDown.Retrieve()) << endl;
			while(defaultPlayer->controls.moveDown.NextPosition())
				output << "bind moveDown " << KeyString(defaultPlayer->controls.moveDown.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.moveLeft.IsEmpty())
		{
			defaultPlayer->controls.moveLeft.FirstPosition();
			output << "bind moveLeft " << KeyString(defaultPlayer->controls.moveLeft.Retrieve()) << endl;
			while(defaultPlayer->controls.moveLeft.NextPosition())
				output << "bind moveLeft " << KeyString(defaultPlayer->controls.moveLeft.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.moveRight.IsEmpty())
		{
			defaultPlayer->controls.moveRight.FirstPosition();
			output << "bind moveRight " << KeyString(defaultPlayer->controls.moveRight.Retrieve()) << endl;
			while(defaultPlayer->controls.moveRight.NextPosition())
				output << "bind moveRight " << KeyString(defaultPlayer->controls.moveRight.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.moveUp.IsEmpty())
		{
			defaultPlayer->controls.moveUp.FirstPosition();
			output << "bind moveUp " << KeyString(defaultPlayer->controls.moveUp.Retrieve()) << endl;
			while(defaultPlayer->controls.moveUp.NextPosition())
				output << "bind moveUp " << KeyString(defaultPlayer->controls.moveUp.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.quickMouseLook.IsEmpty())
		{
			defaultPlayer->controls.quickMouseLook.FirstPosition();
			output << "bind quickMouseLook " << KeyString(defaultPlayer->controls.quickMouseLook.Retrieve()) << endl;
			while(defaultPlayer->controls.quickMouseLook.NextPosition())
				output << "bind quickMouseLook " << KeyString(defaultPlayer->controls.quickMouseLook.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.rollLeft.IsEmpty())
		{
			defaultPlayer->controls.rollLeft.FirstPosition();
			output << "bind rollLeft " << KeyString(defaultPlayer->controls.rollLeft.Retrieve()) << endl;
			while(defaultPlayer->controls.rollLeft.NextPosition())
				output << "bind rollLeft " << KeyString(defaultPlayer->controls.rollLeft.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.rollRight.IsEmpty())
		{
			defaultPlayer->controls.rollRight.FirstPosition();
			output << "bind rollRight " << KeyString(defaultPlayer->controls.rollRight.Retrieve()) << endl;
			while(defaultPlayer->controls.rollRight.NextPosition())
				output << "bind rollRight " << KeyString(defaultPlayer->controls.rollRight.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.toggleConsole.IsEmpty())
		{
			defaultPlayer->controls.toggleConsole.FirstPosition();
			output << "bind toggleConsole " << KeyString(defaultPlayer->controls.toggleConsole.Retrieve()) << endl;
			while(defaultPlayer->controls.toggleConsole.NextPosition())
				output << "bind toggleConsole " << KeyString(defaultPlayer->controls.toggleConsole.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.toggleFPS.IsEmpty())
		{
			defaultPlayer->controls.toggleFPS.FirstPosition();
			output << "bind toggleFPS " << KeyString(defaultPlayer->controls.toggleFPS.Retrieve()) << endl;
			while(defaultPlayer->controls.toggleFPS.NextPosition())
				output << "bind toggleFPS " << KeyString(defaultPlayer->controls.toggleFPS.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.toggleLights.IsEmpty())
		{
			defaultPlayer->controls.toggleLights.FirstPosition();
			output << "bind toggleLights " << KeyString(defaultPlayer->controls.toggleLights.Retrieve()) << endl;
			while(defaultPlayer->controls.toggleLights.NextPosition())
				output << "bind toggleLights " << KeyString(defaultPlayer->controls.toggleLights.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.toggleMouseLook.IsEmpty())
		{
			defaultPlayer->controls.toggleMouseLook.FirstPosition();
			output << "bind toggleMouseLook " << KeyString(defaultPlayer->controls.toggleMouseLook.Retrieve()) << endl;
			while(defaultPlayer->controls.toggleMouseLook.NextPosition())
				output << "bind toggleMouseLook " << KeyString(defaultPlayer->controls.toggleMouseLook.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.weaponNext.IsEmpty())
		{
			defaultPlayer->controls.weaponNext.FirstPosition();
			output << "bind weaponNext " << KeyString(defaultPlayer->controls.weaponNext.Retrieve()) << endl;
			while(defaultPlayer->controls.weaponNext.NextPosition())
				output << "bind weaponNext " << KeyString(defaultPlayer->controls.weaponNext.Retrieve()) << endl;
		}
	
		if(!defaultPlayer->controls.weaponPrev.IsEmpty())
		{
			defaultPlayer->controls.weaponPrev.FirstPosition();
			output << "bind weaponPrev " << KeyString(defaultPlayer->controls.weaponPrev.Retrieve()) << endl;
			while(defaultPlayer->controls.weaponPrev.NextPosition())
				output << "bind weaponPrev " << KeyString(defaultPlayer->controls.weaponPrev.Retrieve()) << endl;
		}
	}
	
	void Level::Print(int x, int y, const char* str, unsigned int set)
	{
		glFont.Print(x,y,str, set);
	}
	
	void Level::UpdateConsole(char newChar)
	{
		if(newChar == '\n')
		{
			for (int i=MAX_CONSOLE_HISTORY_LINES - 1; i>0; i--)
			{
				consoleHistory[i] = consoleHistory[i-1];
			}
			consoleHistory[0] = "";
			ConsolePrint(consoleHistory[1]);
			Execute(tolower(consoleHistory[1]));
			
		}
		else if(newChar == OpenArena::KEY_BACK)
		{
			consoleHistory[0] = Left(consoleHistory[0], consoleHistory[0].length()-1);
		}
		else if(!(defaultPlayer->controls.toggleConsole.Contains(newChar)))
		{
			consoleHistory[0] = consoleHistory[0] + newChar;
			/*
			char errmsg[256];
			sprintf(errmsg, "Unhangled keypress: %d", newChar);
			MessageBox(NULL, errmsg, "Balls", MB_OK);
			*/
		}
	}
	
	void Level::ConsolePrint(string line)
	{
		for (int i=MAX_CONSOLE_OUTPUT_LINES - 1; i>0; i--)
		{
			consoleOutput[i] = consoleOutput[i-1];
		}
		consoleOutput[0] = line;
	}
	
	void Level::SetWindow(Window* window)
	{
		_window = window;
	}
	
	Window* Level::GetWindow()
	{
		return _window;
	}
};
