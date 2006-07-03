#include "window.h"

#ifdef __linux
void OpenArena::Window::SwapBuffers()
{
	if(doubleBuffered)
	{
		glXSwapBuffers(display, window);
	}
}
#endif
#ifdef __APPLE__
void OpenArena::Window::SwapBuffers()
{
	if(doubleBuffered)
	{
		glXSwapBuffers(display, window);
	}
}
#endif
#ifdef WIN32
void OpenArena::Window::SwapBuffers()
{
	::SwapBuffers(deviceContext);
}
#endif

#ifdef __linux
void OpenArena::Window::Close()
{
	if(hRC)
	{
		if(!glXMakeCurrent(display, None, NULL))
		{
			printf("Could not release drawing context.\n");
		}
		glXDestroyContext(display, hRC);
		hRC = NULL;
	}

	if(_fullscreen)
	{
		XF86VidModeSwitchToMode(display, screen, &vidMode);
		XF86VidModeSetViewPort(display, screen, 0, 0);
	}
	XCloseDisplay(display);	
}	
#endif
#ifdef __APPLE__
void OpenArena::Window::Close()
{
	if(hRC)
	{
		if(!glXMakeCurrent(display, None, NULL))
		{
			printf("Could not release drawing context.\n");
		}
		glXDestroyContext(display, hRC);
		hRC = NULL;
	}

	if(_fullscreen)
	{
//		XF86VidModeSwitchToMode(display, screen, &vidMode);
//		XF86VidModeSetViewPort(display, screen, 0, 0);
	}
	XCloseDisplay(display);	
}	
#endif
#ifdef WIN32
void OpenArena::Window::Close()
{
	if (_fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true/*false*/);
	}

	if (glContext)
	{
		if (!wglMakeCurrent(NULL, NULL))
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		if (!wglDeleteContext(glContext))
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		glContext=NULL;
	}

	if (deviceContext && !ReleaseDC(window, deviceContext))
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		deviceContext=NULL;
	}

	if (window && !DestroyWindow(window))
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		window=NULL;
	}

	if (!UnregisterClass("OpenArena v0.1.0", instance))
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		instance=NULL;
	}
}//End OpenArena::Window::Close()
#endif

#ifdef __linux
bool OpenArena::Window::Open()
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
	::Window winDummy;
	unsigned int borderDummy;

	display = XOpenDisplay(0);
	screen = DefaultScreen(display);
	XF86VidModeQueryVersion(display, &vidModeMajorVersion, &vidModeMinorVersion);
	printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion, vidModeMinorVersion);

	XF86VidModeGetAllModeLines(display, screen, &modeNum, &modes);
	vidMode = *modes[0];

	int i;
	for(i=0; i<modeNum; i++)
	{
		//Add a check for colordepth here
		if((modes[i]->hdisplay == _width) && (modes[i]->vdisplay == _height))
		{
			bestMode = i;
		}
	}

	vi = glXChooseVisual(display, screen, attrListDbl);
	if(vi == NULL)
		vi = glXChooseVisual(display, screen, attrListSgl);
		doubleBuffered = false;
		printf("Only Singlebuffered Visual!\n");
	}
	else
	{
		doubleBuffered = true;
		printf("Got Doublebuffered Visual!\n");
	}

	glXQueryVersion(display, &glxMajorVersion, & glxMinorVersion);
	printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);

	hRC = glXCreateContext(display, vi, 0, GL_TRUE);
	cmap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
	attributes.colormap = cmap;
	attributes.border_pixel = 0;

	attributes.event_mask = ExposureMask | 
	                        KeyPressMask | KeyReleaseMask |
	                        ButtonPressMask | ButtonReleaseMask | 
//	                        PointerMotionMask | ButtonMotionMask |
	                        StructureNotifyMask;
	
	if(_fullscreen)
	{
		XF86VidModeSwitchToMode(display, screen, modes[bestMode]);
		XF86VidModeSetViewPort(display, screen, 0, 0);
		XFree(modes);

		attributes.override_redirect = true;
		window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, _width, _height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &attributes);
		XWarpPointer(display, None, window, 0, 0, 0, 0, 0, 0);
		XMapRaised(display, window);
		XGrabKeyboard(display, window, true, GrabModeAsync, GrabModeAsync, CurrentTime);
		XGrabPointer(display, window, true, ButtonPressMask, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
		XDefineCursor(display, window, CreateFullscreenCursor());
	}
	else
	{
		window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, _width, _height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &attributes);
		wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", true);
		XSetWMProtocols(display, window, &wmDelete, 1);
		XSetStandardProperties(display, window, GetName(), GetName(), None, NULL, 0, NULL);
		XMapRaised(display, window);
		XDefineCursor(display, window, CreateWindowedCursor());
	}

	glXMakeCurrent(display, window, hRC);
	unsigned int twidth, theight, depth;
	XGetGeometry(display, window, &winDummy, &x, &y, &twidth, &theight, &borderDummy, &depth);
	_colorDepth = (char)depth;
	_height = (short)twidth;
	_width = (short)theight;
	printf("Resolution %dx%d\n", twidth, theight);
	printf("Depth %d\n", depth);
	if(glXIsDirect(display, hRC))
	{
		printf("Congrats, you have Direct Rendering!\n");
	}
	else
	{
		printf("Sorry, no Direct Rendering possible!\n");
	}
	_initializer->Initialize();
	return true;
}
#endif
#ifdef __APPLE__
bool OpenArena::Window::Open()
{
		XVisualInfo* vi;
	Colormap cmap;
	int bestMode = 0;
	int vidModeMajorVersion;
	int vidModeMinorVersion;
	int glxMajorVersion;
	int glxMinorVersion;
	int modeNum;
//	XF86VidModeModeInfo** modes;
	Atom  wmDelete;
	::Window winDummy;
	unsigned int borderDummy;

	display = XOpenDisplay(0);
	screen = DefaultScreen(display);
	//XF86VidModeQueryVersion(display, &vidModeMajorVersion, &vidModeMinorVersion);
	//printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion, vidModeMinorVersion);

	//XF86VidModeGetAllModeLines(display, screen, &modeNum, &modes);
	//vidMode = *modes[0];

	int i;
	for(i=0; i<modeNum; i++)
	{
		//Add a check for colordepth here
	//	if((modes[i]->hdisplay == _width) && (modes[i]->vdisplay == _height))
	//	{
	//		bestMode = i;
	//	}
	}

	vi = glXChooseVisual(display, screen, attrListDbl);
	if(vi == NULL)
	{
		vi = glXChooseVisual(display, screen, attrListSgl);
		doubleBuffered = false;
		printf("Only Singlebuffered Visual!\n");
	}
	else
	{
		doubleBuffered = true;
		printf("Got Doublebuffered Visual!\n");
	}

	glXQueryVersion(display, &glxMajorVersion, & glxMinorVersion);
	printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);

	hRC = glXCreateContext(display, vi, 0, GL_TRUE);
	cmap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
	attributes.colormap = cmap;
	attributes.border_pixel = 0;

	attributes.event_mask = ExposureMask | 
	                        KeyPressMask | KeyReleaseMask |
	                        ButtonPressMask | ButtonReleaseMask | 
//	                        PointerMotionMask | ButtonMotionMask |
	                        StructureNotifyMask;
	
	if(_fullscreen)
	{
	//	XF86VidModeSwitchToMode(display, screen, modes[bestMode]);
	//	XF86VidModeSetViewPort(display, screen, 0, 0);
	//	XFree(modes);

		attributes.override_redirect = true;
		window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, _width, _height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &attributes);
		XWarpPointer(display, None, window, 0, 0, 0, 0, 0, 0);
		XMapRaised(display, window);
		XGrabKeyboard(display, window, true, GrabModeAsync, GrabModeAsync, CurrentTime);
		XGrabPointer(display, window, true, ButtonPressMask, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
		XDefineCursor(display, window, CreateFullscreenCursor());
	}
	else
	{
		window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, _width, _height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &attributes);
		wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", true);
		XSetWMProtocols(display, window, &wmDelete, 1);
		XSetStandardProperties(display, window, GetName(), GetName(), None, NULL, 0, NULL);
		XMapRaised(display, window);
		XDefineCursor(display, window, CreateWindowedCursor());
	}

	glXMakeCurrent(display, window, hRC);
	unsigned int twidth, theight, depth;
	XGetGeometry(display, window, &winDummy, &x, &y, &twidth, &theight, &borderDummy, &depth);
	_colorDepth = (char)depth;
	_height = (short)twidth;
	_width = (short)theight;
	printf("Resolution %dx%d\n", twidth, theight);
	printf("Depth %d\n", depth);
	if(glXIsDirect(display, hRC))
	{
		printf("Congrats, you have Direct Rendering!\n");
	}
	else
	{
		printf("Sorry, no Direct Rendering possible!\n");
	}
	_initializer->Initialize();
	return true;
}
#endif
#ifdef WIN32
bool OpenArena::Window::Open()
{
	unsigned int PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)_width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)_height;

	instance	= GetModuleHandle(NULL);
	wc.style	= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenArena v0.1.0";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (_fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = _width;
		dmScreenSettings.dmPelsHeight = _height;
		dmScreenSettings.dmBitsPerPel = _colorDepth;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;


		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","OpenArena",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
				_fullscreen = false;
			else
			{

				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return false;
			}
		}
	}

	if (_fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(/*true*/false);
	}
	else
	{
		ShowCursor(false);
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

	if (!(window = CreateWindowEx(dwExStyle, "OpenArena v0.1.0", GetName(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, NULL, NULL, instance, NULL)))
	{
		Close();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	static	PIXELFORMATDESCRIPTOR pfd={sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, _colorDepth, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

	if (!(deviceContext=GetDC(window)))
	{
		Close();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (!(PixelFormat=ChoosePixelFormat(deviceContext,&pfd)))
	{
		Close();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!SetPixelFormat(deviceContext,PixelFormat,&pfd))
	{
		Close();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (!(glContext=wglCreateContext(deviceContext)))
	{
		Close();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!wglMakeCurrent(deviceContext,glContext))
	{
		Close();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(window,SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);
	_resizer->Resize(_width, _height);

	if (!_initializer->Initialize())
	{
		Close();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}
#endif

bool OpenArena::Window::Open(string title, int width, int height, int bits, bool fullscreenflag)
{
	_fullscreen = fullscreenflag;
	_width = width;
	_height = height;
	_colorDepth = bits;
	_name = title;

	return Open();
}

OpenArena::Window::Window()
{
	_initializer = new Initializer();
	_resizer = new Resizer();
}

OpenArena::Window::~Window()
{
}

void OpenArena::Window::SetInitializer(OpenArena::Window::Initializer* initializer)
{
	_initializer = initializer;
}

void OpenArena::Window::SetResizer(OpenArena::Window::Resizer* resizer)
{
	_resizer = resizer;
}

void OpenArena::Window::Resizer::Resize(GLsizei width, GLsizei height)
{
	if (height==0)
		height=1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

int OpenArena::Window::Initializer::Initialize()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	return true;
}

void OpenArena::Window::Resize(GLsizei width, GLsizei height)
{
	_resizer->Resize(width, height);
}

#ifdef __linux
Display* OpenArena::Window::GetDisplay()
{
	return display;
}
#endif

#ifdef __APPLE__
Display* OpenArena::Window::GetDisplay()
{
	return display;
}
#endif

#ifdef __linux
Vec2i OpenArena::Window::GetMousePosition()
{
	::Window rootWindow;
	::Window childWindow;
	int rootX;
	int rootY;
	int mouseX;
	int mouseY;
	unsigned int mask;
	if(!XQueryPointer(display, window, &rootWindow, &childWindow, &rootX, &rootY, &mouseX, &mouseY, &mask))
	{
		return Vec2i(-1,-1);
	}
	else
	{
		return Vec2i(mouseX, mouseY);
	}
}
#endif
#ifdef __APPLE__
OpenArena::Vec2i OpenArena::Window::GetMousePosition()
{
	::Window rootWindow;
	::Window childWindow;
	int rootX;
	int rootY;
	int mouseX;
	int mouseY;
	unsigned int mask;
	if(!XQueryPointer(display, window, &rootWindow, &childWindow, &rootX, &rootY, &mouseX, &mouseY, &mask))
	{
		return Vec2i(-1,-1);
	}
	else
	{
		return Vec2i(mouseX, mouseY);
	}
}
#endif
#ifdef WIN32
OpenArena::Vec2i OpenArena::Window::GetMousePosition()
{
		POINT pos;
	GetCursorPos(&pos);
	return Vec2i(pos.x, pos.y);
}
#endif

#ifdef __linux
void OpenArena::Window::SetMousePosition(Vec2i pos)
{
	Vec2i middle = Vec2i(_width, _height)/2;
	XWarpPointer(display, None, window, 0, 0, 0, 0, middle.x, middle.y);
}
#endif
#ifdef __APPLE__
void OpenArena::Window::SetMousePosition(Vec2i pos)
{
	Vec2i middle = Vec2i(_width, _height)/2;
	XWarpPointer(display, None, window, 0, 0, 0, 0, middle.x, middle.y);
}
#endif
#ifdef WIN32
void OpenArena::Window::SetMousePosition(Vec2i pos)
{
	SetCursorPos(pos.x, pos.y);
}
#endif

#ifdef __linux
Cursor OpenArena::Window::CreateWindowedCursor()
{
	return CreateFullscreenCursor();
}

Cursor OpenArena::Window::CreateFullscreenCursor()
{
	Pixmap pixmap = XCreatePixmap(display, window, 1, 1, 1);
	XColor color;
	color.pixel = 0;
	color.red = 0;
	color.flags = DoRed;
	Cursor cur = XCreatePixmapCursor(display, pixmap, pixmap, &color, &color, 0, 0);
	XFreePixmap(display, pixmap);
	return cur;
}
#endif
#ifdef __APPLE__
Cursor OpenArena::Window::CreateWindowedCursor()
{
	return CreateFullscreenCursor();
}

Cursor OpenArena::Window::CreateFullscreenCursor()
{
	Pixmap pixmap = XCreatePixmap(display, window, 1, 1, 1);
	XColor color;
	color.pixel = 0;
	color.red = 0;
	color.flags = DoRed;
	Cursor cur = XCreatePixmapCursor(display, pixmap, pixmap, &color, &color, 0, 0);
	XFreePixmap(display, pixmap);
	return cur;
}
#endif

