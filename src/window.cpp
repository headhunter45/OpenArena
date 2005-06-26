#include "../include/window.h"
void OpenArena::Window::SwapBuffers()
{
#ifdef __linux
	if(doubleBuffered)
	{
		glXSwapBuffers(display, window);
	}
#endif
#ifdef WIN32
	::SwapBuffers(deviceContext);
#endif
}

void OpenArena::Window::Close()
{
#ifdef WIN32
	if (fullscreen)
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
#endif
}

bool OpenArena::Window::Open()
{
	unsigned int PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;

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

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bpp;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;


		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","OpenArena",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
				fullscreen = false;
			else
			{

				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return false;
			}
		}
	}

	if (fullscreen)
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

	if (!(window = CreateWindowEx(dwExStyle, "OpenArena v0.1.0", name.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, NULL, NULL, instance, NULL)))
	{
		Close();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	static	PIXELFORMATDESCRIPTOR pfd={sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, bpp, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

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
	OnResize(width, height);

	if (!OnInit())
	{
		Close();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

bool OpenArena::Window::Open(string title, int width, int height, int bits, bool fullscreenflag)
{
	fullscreen = fullscreenflag;
	width = width;
	height = height;
	bpp = bits;
	name = title;

	return Open();
}

OpenArena::Window::Window()
{
	OnInit = OpenArena::DefaultInit;
	OnResize = OpenArena::DefaultResize;
}

OpenArena::Window::~Window()
{
}

void OpenArena::Window::SetOnInit(InitFunc function)
{
	OnInit = function;
}

void OpenArena::Window::SetOnResize(ResizeFunc function)
{
	OnResize = function;
}

int OpenArena::DefaultInit()
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

void OpenArena::DefaultResize(GLsizei width, GLsizei height)
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
