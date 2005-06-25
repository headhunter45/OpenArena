////////////////////////////////////////////////////////////////////////////////
//
//	Module:		linux.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	06-19-2005
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
#ifdef __linux

//include necessary header files
#include "../include/main.h"
using namespace std;

void InitControls();
int InitGL();
void KillGLWindow();

static int attrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};
static int attrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions

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

int DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();
	if(g_Screen.doubleBuffered)
	{
		glXSwapBuffers(g_Screen.display, g_Screen.window);
	}
	return 1;
}

//
//void InitControls()
//  Purpose:
//	    Initializes controls by loading the default control config file "my.cfg".
void InitControls()
{
	if (!level.LoadConfig("my.cfg"))
		level.LoadConfig();
}

//
//int InitGL(GLvoid)
//	Purpose:
//		To do all required setup before creating an OpenGL window
int InitGL(GLvoid)
{
	level.LoadGLTextures();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/*lighting disabled temporarily
	glLightfv(GL_LIGHT1, GL_AMBIENT, level.LightAmbient);
	for(index=0; index<level.numLights; index++)
	{
	glLightfv(GL_LIGHT1, GL_DIFFUSE, level.light[index].color);
	glLightfv(GL_LIGHT1, GL_POSITION, level.light[index].coords);
	}

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	*/
	//BuildFont();
	return true;
}

//
//void KillGLWindow()
//	Purpose:
//		To do all required setup before creating an OpenGL window
void KillGLWindow()
{
	if(g_Screen.hRC)
	{
		if(!glXMakeCurrent(g_Screen.display, None, NULL))
		{
			printf("Could not release drawing context.\n");
		}
		glXDestroyContext(g_Screen.display, g_Screen.hRC);
		g_Screen.hRC = NULL;
	}
	
	if(g_Screen.fullscreen)
	{
		XF86VidModeSwitchToMode(g_Screen.display, g_Screen.screen, &g_Screen.vidMode);
		XF86VidModeSetViewPort(g_Screen.display, g_Screen.screen, 0, 0);
	}
	XCloseDisplay(g_Screen.display);
}

//
//bool CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag)
//	Purpose:
//		
bool CreateGLWindow(string title, int width, int height, int bits, bool fullscreenflag)
{
	XVisualInfo* vi;
	Colormap cmap;
	int bestMode = 0;
	int vidModeMajorVersion;
	int vidModeMinorVersion;
	int glxMajorVersion;
	int glxMinorVersion;
	int modeNum;
	XF86VidModeModeInfo** modes;
	Atom  wmDelete;
	Window winDummy;
	unsigned int borderDummy;
	
	g_Screen.name = title;
	g_Screen.width = width;
	g_Screen.height = height;
	g_Screen.bpp = bits;
	g_Screen.fullscreen = fullscreenflag;

	g_Screen.display = XOpenDisplay(0);
	g_Screen.screen = DefaultScreen(g_Screen.display);
	XF86VidModeQueryVersion(g_Screen.display, &vidModeMajorVersion, &vidModeMinorVersion);
	printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion, vidModeMinorVersion);
	
	XF86VidModeGetAllModeLines(g_Screen.display, g_Screen.screen, &modeNum, &modes);
	g_Screen.vidMode = *modes[0];
	
	int i;
	for(i=0; i<modeNum; i++)
	{
		//Add a check for colordepth here
		if((modes[i]->hdisplay == width) && (modes[i]->vdisplay == height))
		{
			bestMode = i;
		}
	}
	
	vi = glXChooseVisual(g_Screen.display, g_Screen.screen, attrListDbl);
	if(vi == NULL)
	{
		vi = glXChooseVisual(g_Screen.display, g_Screen.screen, attrListSgl);
		g_Screen.doubleBuffered = false;
		printf("Only Singlebuffered Visual!\n");
	}
	else
	{
		g_Screen.doubleBuffered = true;
		printf("Got Doublebuffered Visual!\n");
	}
	
	glXQueryVersion(g_Screen.display, &glxMajorVersion, & glxMinorVersion);
	printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);
	
	g_Screen.hRC = glXCreateContext(g_Screen.display, vi, 0, GL_TRUE);
	cmap = XCreateColormap(g_Screen.display, RootWindow(g_Screen.display, vi->screen), vi->visual, AllocNone);
	g_Screen.attributes.colormap = cmap;
	g_Screen.attributes.border_pixel = 0;
	
	if(g_Screen.fullscreen)
	{
		XF86VidModeSwitchToMode(g_Screen.display, g_Screen.screen, modes[bestMode]);
		XF86VidModeSetViewPort(g_Screen.display, g_Screen.screen, 0, 0);
		XFree(modes);
		
		g_Screen.attributes.override_redirect = true;
		g_Screen.attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
		g_Screen.window = XCreateWindow(g_Screen.display, RootWindow(g_Screen.display, vi->screen), 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &g_Screen.attributes);
		XWarpPointer(g_Screen.display, None, g_Screen.window, 0, 0, 0, 0, 0, 0);
		XMapRaised(g_Screen.display, g_Screen.window);
		XGrabKeyboard(g_Screen.display, g_Screen.window, true, GrabModeAsync, GrabModeAsync, CurrentTime);
		XGrabPointer(g_Screen.display, g_Screen.window, true, ButtonPressMask, GrabModeAsync, GrabModeAsync, g_Screen.window, None, CurrentTime);
	}
	else
	{
		g_Screen.attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
		g_Screen.window = XCreateWindow(g_Screen.display, RootWindow(g_Screen.display, vi->screen), 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &g_Screen.attributes);
		wmDelete = XInternAtom(g_Screen.display, "WM_DELETE_WINDOW", true);
		XSetWMProtocols(g_Screen.display, g_Screen.window, &wmDelete, 1);
		XSetStandardProperties(g_Screen.display, g_Screen.window, title.c_str(), title.c_str(), None, NULL, 0, NULL);
		XMapRaised(g_Screen.display, g_Screen.window);
	}
	
	glXMakeCurrent(g_Screen.display, g_Screen.window, g_Screen.hRC);
	unsigned int twidth, theight, depth;
	XGetGeometry(g_Screen.display, g_Screen.window, &winDummy, &g_Screen.x, &g_Screen.y, &twidth, &theight, &borderDummy, &depth);
	g_Screen.bpp = (char)depth;
	g_Screen.height = (short)twidth;
	g_Screen.width = (short)theight;
	printf("Depth %d\n", g_Screen.bpp);
	if(glXIsDirect(g_Screen.display, g_Screen.hRC))
	{
		printf("Congrats, you have Direct Rendering!\n");
	}
	else
	{
		printf("Sorry, no Direct Rendering possible!\n");
	}
	InitGL();
	return true;
}

int main(int argc, char** argv)
{
	XEvent event;
	bool done = false;
	
	g_Screen.fullscreen = false;
	CreateGLWindow("Blah Blah BLah", 640, 480, 24, false);
	while(!done)
	{
		while(XPending(g_Screen.display) > 0)
		{
			XNextEvent(g_Screen.display, &event);
			switch(event.type)
			{
				case Expose:
					if(event.xexpose.count != 0)
					{
						break;
					}
					DrawGLScene();
					break;
				case ConfigureNotify:
					if((event.xconfigure.width != g_Screen.width) || (event.xconfigure.height != g_Screen.height))
					{
						g_Screen.width = event.xconfigure.width;
						g_Screen.height = event.xconfigure.height;
						printf("Resize event\n");
						ResizeGLScene(event.xconfigure.width, event.xconfigure.height);
					}
					break;
				case ButtonPress:
					done = true;
					break;
				case KeyPress:
					if(XLookupKeysym(&event.xkey, 0) == XK_Escape)
					{
						done = true;
					}
					if(XLookupKeysym(&event.xkey, 0) == XK_F1)
					{
						KillGLWindow();
						g_Screen.fullscreen = !g_Screen.fullscreen;
						CreateGLWindow("Blah Blah Blah", 640, 480, 24, g_Screen.fullscreen);
					}
					break;
				case ClientMessage:
					if(*XGetAtomName(g_Screen.display, event.xclient.message_type) == *"WM_PROTOCOLS")
					{
						printf("Exiting sanely...\n");
						done = true;
					}
					break;
				default:
					break;
			}
		}
		DrawGLScene();
	}
	KillGLWindow();
	exit(0);
}
				
#endif
