////////////////////////////////////////////////////////////////////////////////
//
//	Module:		level.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	10-09-2003
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

#include "../include/level.h"

#pragma comment(lib, "bass.lib")

using namespace std;

LEVEL::LEVEL()
{

	consoleHistory[0] = "hello0";
	consoleHistory[1] = "hello1";
	consoleHistory[MAX_CONSOLE_HISTORY_LINES-2] = "hello3";
	consoleHistory[MAX_CONSOLE_HISTORY_LINES-1] = "hello4";

	textureNames = NULL;
	numTextures = 0;

	screen.name = "OpenArena";

	showFPS = false;
	showConsole = false;

	nextLevel = "intro.map";
		gamedir = "oa/";
	sound = true;

	defaultPlayer = new PLAYER;

	numTriangles = 0;
	triangles = NULL;
	/*
	for(int x=0; x<4; x++)
	LightAmbient[x] = 5;
	*/
	//Player Stuff
	mouseSpeed = 5;
	turnSpeed = 1.0f;
	moveSpeed = .2f;
	mlook = true;
}

LEVEL::~LEVEL()
{
	if(defaultPlayer)
	{
		try
		{
			delete defaultPlayer;
		}
		catch(...)
		{
		}
		defaultPlayer = NULL;
	}
}




bool LEVEL::LoadMap(string mapname)
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

		MessageBox(NULL,tmpChar,"ERROR",MB_OK|MB_ICONEXCLAMATION);
		delete [] tmpChar;
		return false;
	}

	//Gravity
	input >> readBuffer;
	gravity = (float)atof(readBuffer.c_str());

	//Number of triangles
	input >> readBuffer;
	numTriangles = Integer(readBuffer);

	//Triangle Data
	triangles = new TRIANGLE[numTriangles];
	for(unsigned int i=0; i<numTriangles; i++)
	{
		//TextureID
		input >> readBuffer;
		triangles[i].texID = Integer(readBuffer);

		for(unsigned int i2=0; i2<3; i2++)
		{
			//Vertex Data
			input >> readBuffer;
			triangles[i].vertecies[i2].x = atof(readBuffer.c_str());
			input >> readBuffer;
			triangles[i].vertecies[i2].y = atof(readBuffer.c_str());
			input >> readBuffer;
			triangles[i].vertecies[i2].z = atof(readBuffer.c_str());
			input >> readBuffer;
			triangles[i].texCoords[i2].x = (float)atof(readBuffer.c_str());
			input >> readBuffer;
			triangles[i].texCoords[i2].y = (float)atof(readBuffer.c_str());
		}

		//Normal
		input >> readBuffer;

		triangles[i].normal.x = atof(readBuffer.c_str());
		input >> readBuffer;
		triangles[i].normal.y = atof(readBuffer.c_str());
		input >> readBuffer;
		triangles[i].normal.z = atof(readBuffer.c_str());
	}

	//Number of textures;
	input >> readBuffer;
	numTextures = Integer(readBuffer);

	//Texture data
	textureNames = new string[numTextures];
	for(unsigned int i=0; i<numTextures; i++)
	{
		input >> textureNames[i];	
	}

	//BGM
	input >> bgm;

	//LoadGLTextures();
	//Build display list
	if (sound)
	{
		BASS_Init(-1, 44100, BASS_DEVICE_LEAVEVOL, g_hWnd);
		BASS_Start();
		BASS_CDInit(NULL, BASS_DEVICE_LEAVEVOL);

		if(bgm.length()>=4)
		{
			if( toupper(bgm[0]) == 'C' &&
				toupper(bgm[1]) == 'D' &&
				toupper(bgm[2]) == 'A')
			{
				bgmCDA = Integer(bgm.substr(3,bgm.length()));
				BASS_CDPlay(bgmCDA, 1, 0);
			}
			else
			{
				bgmCDA=0;
				string tmpstr = gamedir + "music/bgm/" + bgm;
				bgmStream = BASS_StreamCreateFile(0, (void*)tmpstr.c_str(), 0, 0, BASS_STREAM_AUTOFREE);
				BASS_StreamPlay(bgmStream, 1, BASS_SAMPLE_LOOP);					
			}
		}
	}

	return true;
}
void LEVEL::LoadMap()
{
	LoadMap(nextLevel);
}

void LEVEL::SaveMap(string mapname)
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

		MessageBox(NULL,tmpChar,"ERROR",MB_OK|MB_ICONEXCLAMATION);
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
			output << triangles[i].vertecies[i2].x << " "
				   << triangles[i].vertecies[i2].y << " "
				   << triangles[i].vertecies[i2].z << " "
				   << triangles[i].texCoords[i2].x << " "
				   << triangles[i].texCoords[i2].y << endl;
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

void LEVEL::Render()
{
	glPushMatrix();	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Move the camera to where the player is or more precisely move to world so the camer is where the playe is
	defaultPlayer->camera.Look();
///*
	for (uint32 i=0; i<numTriangles; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[triangles[i].texID].ID());//Bind this triangle's texture
		glBegin(GL_TRIANGLES);
//		glNormal3f((GLfloat)triangles[i].normal.x, (GLfloat)triangles[i].normal.y, (GLfloat)triangles[i].normal.z);
		for (uint32 i2=0; i2<3; i2++)
		{
			glTexCoord2f(triangles[i].texCoords[i2].x,
						 triangles[i].texCoords[i2].y);
			glVertex3f((GLfloat)triangles[i].vertecies[i2].x,
					   (GLfloat)triangles[i].vertecies[i2].y,
					   (GLfloat)triangles[i].vertecies[i2].z);
		}
		glEnd();
	}
/**/

	/*
	glBindTexture(GL_TEXTURE_2D, 1);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0,0);
		glVertex3f(-10, -10,-5);
		glTexCoord2f(0,2);
		glVertex3f(-10,10,-5);
		glTexCoord2f(2,0);
		glVertex3f(10,-10,-5);
	glEnd();
	/**/

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
		glOrtho(0, screen.width, 0, screen.height, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex2i(0,screen.height/2);
			glTexCoord2f(0,1);
			glVertex2i(0,screen.height);
			glTexCoord2f(1,1);
			glVertex2i(screen.width,screen.height);
			glTexCoord2f(1,0);
			glVertex2i(screen.width,screen.height/2);
		glEnd();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		
		glDisable(GL_LIGHTING);

		//enable blending
		glEnable(GL_BLEND);

		//render the console background
		for(unsigned int i=0; i<MAX_CONSOLE_LINES; i++)
		{
			Print(30, glFont.ScreenHeight() - i*20, consoleHistory[MAX_CONSOLE_LINES-i-1].c_str(), 0);
		}

		//disable blending
		glDisable(GL_BLEND);

		//re-enable lighting and depth testing
		//glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
}

void LEVEL::UnloadMap()
{
	//Stop audio
	BASS_StreamFree(bgmStream);
	BASS_Stop();
	BASS_CDFree();
	BASS_Free();

	//Delete display list

	if(triangles)
	{
		try
		{
			delete [] triangles;
		}
		catch(...)
		{
		}
	}

	if (textureNames)
	{
		try
		{
		delete [] textureNames;
		}
		catch(...)
		{
		}
	}
}

void LEVEL::LoadGLTextures()
{
	
	/*GLfloat light[4] = {1.0f,1.0f,1.0f,0.5f};
    glLightfv(GL_LIGHT1, GL_AMBIENT, light);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);*/


	textures = new GL_MY_TEXTURE[numTextures];

	for(uint32 i=0; i<numTextures; i++)
	{
		if(!textures[i].Load(gamedir + "textures/" + textureNames[i]))
			textures[i].Load(DEFAULT_TEXTURE_NAME);
	}
	
	if(!glFont.BuildFont((gamedir + "textures/menu/font.bmp").c_str()))
		glFont.BuildFont("oa/textures/menu/font.bmp");

	//Load the console background image
	if(!menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].Load(gamedir + "textures/menu/con_back.tga"))
		menuTextures[GL_MY_TEXTURE_CONSOLEBACKGROUND].Load("oa/textures/menu/con_back.bmp");


}

uint32 LEVEL::FPS()
{
	static uint32 fps=0;
	static uint32 fps2=0;
	static float last=0.0f;  // might need to change to double

	float time=GetTickCount()*.001f;

	++fps;

	if(time>last+1)
	{
		last=time;
		fps2 = fps;
		fps=0;
	}
	return fps2;
}

void LEVEL::Execute(string cmd)
{
	string command;
	
	uint32 i=0xFFFFFFFF;
	while(word(cmd, ++i) != "")
	{
		command = word(cmd, i);
		
		if(command == "set")
		{
			command = tolower(word(cmd, ++i));
			
			if(command == "turnspeed")
			{
				turnSpeed = (float)atof(word(cmd, ++i).c_str());//Floating(word(cmd, ++i));
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
			else if(command == "screenwidth")
			{
				screen.width = Integer(word(cmd, ++i));
			}
			else if(command == "screenheight")
			{
				screen.height = Integer(word(cmd, ++i));
			}
			else if(command == "fullscreen")
			{
				screen.fullscreen = Truth(word(cmd, ++i));
			}
		}
		else if(command == "bind")
		{
			command = tolower(word(cmd, ++i));

			if(command == "forward")
			{
				defaultPlayer->controls.forward.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "backward")
			{
				defaultPlayer->controls.backward.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookleft")
			{
				defaultPlayer->controls.lookLeft.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookright")
			{
				defaultPlayer->controls.lookRight.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookup")
			{
				defaultPlayer->controls.lookUp.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookdown")
			{
				defaultPlayer->controls.lookDown.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "moveup")
			{
				defaultPlayer->controls.moveUp.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "movedown")
			{
				defaultPlayer->controls.moveDown.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "moveleft")
			{
				defaultPlayer[0].controls.moveLeft.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "moveright")
			{
				defaultPlayer[0].controls.moveRight.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "fireprimary")
			{
				defaultPlayer->controls.firePrimary.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "firesecondary")
			{
				defaultPlayer->controls.fireSecondary.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "weapnext")
			{
				defaultPlayer->controls.weaponNext.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "weapprev")
			{
				defaultPlayer->controls.weaponPrev.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "togglelights" || command == "togglelighting")
			{
				defaultPlayer->controls.toggleLights.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "togglefps")
			{
				defaultPlayer->controls.toggleFPS.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "toggleconsole")
			{
				defaultPlayer->controls.toggleConsole.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "togglemouselook")
			{
				defaultPlayer->controls.toggleMouseLook.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "quickmouselook")
			{
				defaultPlayer->controls.quickMouseLook.Insert(KeyName(word(cmd, ++i)));
			}
		}
		else if(command == "map")
		{
			nextLevel = word(cmd, ++i);
		}
	}
}

void LEVEL::ParseCmds(LPSTR lpCmdLine)
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
				defaultPlayer->controls.forward.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "backward")
			{
				defaultPlayer->controls.backward.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookleft")
			{
				defaultPlayer->controls.lookLeft.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookright")
			{
				defaultPlayer->controls.lookRight.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookup")
			{
				defaultPlayer->controls.lookUp.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "lookdown")
			{
				defaultPlayer->controls.lookDown.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "moveup")
			{
				defaultPlayer->controls.moveUp.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "movedown")
			{
				defaultPlayer->controls.moveDown.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "fireprimary")
			{
				defaultPlayer->controls.firePrimary.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "firesecondary")
			{
				defaultPlayer->controls.fireSecondary.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "weapnext")
			{
				defaultPlayer->controls.weaponNext.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "weapprev")
			{
				defaultPlayer->controls.weaponPrev.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "togglelights" || command == "togglelighting")
			{
				defaultPlayer->controls.toggleLights.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "togglefps")
			{
				defaultPlayer->controls.toggleFPS.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "toggleconsole")
			{
				defaultPlayer->controls.toggleConsole.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "togglemouselook")
			{
				defaultPlayer->controls.toggleMouseLook.Insert(KeyName(word(cmd, ++i)));
			}
			else if(command == "quickmouselook")
			{
				defaultPlayer->controls.quickMouseLook.Insert(KeyName(word(cmd, ++i)));
			}
		}
		else if(command == "+map")
		{
			nextLevel = word(cmd, ++i);
		}
	}
}

void LEVEL::LoadConfig()
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
bool LEVEL::LoadConfig(string cfgname)
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

void LEVEL::SaveConfig(string cfgname)
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
	output << "set screenwidth " << screen.width << endl;
	output << "set screenheight " << screen.height << endl;
	output << "set colordepth " << screen.bpp << endl;
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

void LEVEL::Print(int x, int y, const char* str, unsigned int set)
{
	glFont.Print(x,y,str, set);
}