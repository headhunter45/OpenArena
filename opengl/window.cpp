// clang-format off
#include "window.h"
#include <windows.h>
#include "..\opengl.h"

// clang-format on

namespace OpenArena {
namespace OpenGL {
namespace {
using OpenArena::Vec2i;
using std::string;
}  // End namespace

void Window::SwapBuffers() {
#if defined USE_GLX
  if (doubleBuffered) {
    glXSwapBuffers(display, window);
  }
#elif defined USE_AGL
  aglSwapBuffers(_aglContext);
#elif defined USE_CGL
  CGLFlushDrawable(cglContext);
#elif defined USE_WGL
  ::SwapBuffers(deviceContext);
#endif
}

bool Window::Open() {
#if defined USE_GLX
  XVisualInfo* vi;
  Colormap cmap;
  int bestMode = 0;
  int vidModeMajorVersion;
  int vidModeMinorVersion;
  int glxMajorVersion;
  int glxMinorVersion;
  int modeNum;
#if defined HAVE_XF86VIDMODE
  XF86VidModeModeInfo** modes;
#endif
  Atom wmDelete;
  ::Window winDummy;
  unsigned int borderDummy;

  display = XOpenDisplay(0);
  screen = DefaultScreen(display);

#if defined HAVE_XF86VIDMODE
  XF86VidModeQueryVersion(display, &vidModeMajorVersion, &vidModeMinorVersion);
  printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion, vidModeMinorVersion);

  XF86VidModeGetAllModeLines(display, screen, &modeNum, &modes);
  vidMode = *modes[0];

  int i;
  for (i = 0; i < modeNum; i++) {
    // Add a check for colordepth here
    if ((modes[i]->hdisplay == _width) && (modes[i]->vdisplay == _height)) {
      bestMode = i;
    }
  }
#endif

  vi = glXChooseVisual(display, screen, attrListDbl);
  if (vi == NULL) {
    vi = glXChooseVisual(display, screen, attrListSgl);
    doubleBuffered = false;
    printf("Only Singlebuffered Visual!\n");
  } else {
    doubleBuffered = true;
    printf("Got Doublebuffered Visual!\n");
  }

  glXQueryVersion(display, &glxMajorVersion, &glxMinorVersion);
  printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);

  hRC = glXCreateContext(display, vi, 0, GL_TRUE);
  cmap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
  attributes.colormap = cmap;
  attributes.border_pixel = 0;

  attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                          //	                        PointerMotionMask | ButtonMotionMask |
                          StructureNotifyMask;

  if (_fullscreen) {
#if defined HAVE_XF86VIDMODE
    XF86VidModeSwitchToMode(display, screen, modes[bestMode]);
    XF86VidModeSetViewPort(display, screen, 0, 0);
    XFree(modes);
#endif

    attributes.override_redirect = true;
    window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, _width, _height, 0, vi->depth, InputOutput,
                           vi->visual, CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &attributes);
    XWarpPointer(display, None, window, 0, 0, 0, 0, 0, 0);
    XMapRaised(display, window);
    XGrabKeyboard(display, window, true, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(display, window, true, ButtonPressMask, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
    XDefineCursor(display, window, CreateFullscreenCursor());
  } else {
    window = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, _width, _height, 0, vi->depth, InputOutput,
                           vi->visual, CWBorderPixel | CWColormap | CWEventMask, &attributes);
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
  if (glXIsDirect(display, hRC)) {
    printf("Congrats, you have Direct Rendering!\n");
  } else {
    printf("Sorry, no Direct Rendering possible!\n");
  }
  _initializer->Initialize();
  return true;
#elif defined USE_AGL
  OSStatus err = noErr;
  SetRect(&_bounds, 0, 0, 640, 480);
  err = CreateNewWindow(kDocumentWindowClass,
                        kWindowStandardHandlerAttribute | kWindowCloseBoxAttribute | kWindowFullZoomAttribute
                            | kWindowCollapseBoxAttribute,
                        &_bounds, &_window);
  if (err != noErr) {
    return false;
  }

  RepositionWindow(_window, NULL, kWindowCascadeOnMainScreen);

  AGLDevice* devices = NULL;
  GLint deviceCount = 0;
  GLint attributes[] = {AGL_ACCELERATED, AGL_NO_RECOVERY, AGL_RGBA, AGL_DOUBLEBUFFER, AGL_NONE};
  AGLPixelFormat pixelFormat;

  pixelFormat = aglChoosePixelFormat(devices, deviceCount, attributes);
  _aglContext = aglCreateContext(pixelFormat, NULL);
  if (!_aglContext) {
    exit(5);
  }

  aglDestroyPixelFormat(pixelFormat);

  if (!aglSetCurrentContext(_aglContext)) {
    exit(6);
  }

  if (!aglSetDrawable(_aglContext, GetWindowPort(_window))) {
    exit(7);
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  aglSwapBuffers(_aglContext);
  ShowWindow(_window);
#elif defined USE_CGL
#error undefined method
#elif defined USE_WGL
  unsigned int PixelFormat;
  WNDCLASS wc;
  DWORD dwExStyle;
  DWORD dwStyle;
  RECT WindowRect;
  WindowRect.left = (long)0;
  WindowRect.right = (long)_width;
  WindowRect.top = (long)0;
  WindowRect.bottom = (long)_height;

  instance = GetModuleHandle(NULL);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = (WNDPROC)WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = instance;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "OpenArena v0.1.0";

  if (!RegisterClass(&wc)) {
    MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  if (_fullscreen) {
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = _width;
    dmScreenSettings.dmPelsHeight = _height;
    dmScreenSettings.dmBitsPerPel = _colorDepth;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
      if (MessageBox(NULL,
                     "The Requested Fullscreen Mode Is Not Supported By\nYour "
                     "Video Card. Use Windowed Mode Instead?",
                     "OpenArena", MB_YESNO | MB_ICONEXCLAMATION)
          == IDYES)
        _fullscreen = false;
      else {
        MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
        return false;
      }
    }
  }

  if (_fullscreen) {
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle = WS_POPUP;
    ShowCursor(/*true*/ false);
  } else {
    ShowCursor(false);
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;
  }

  AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

  if (!(window = CreateWindowEx(dwExStyle, "OpenArena v0.1.0", GetName(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
                                0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL,
                                NULL, instance, NULL))) {
    Close();
    MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),
                                      1,
                                      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                                      PFD_TYPE_RGBA,
                                      static_cast<BYTE>(_colorDepth),
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      16,
                                      0,
                                      0,
                                      PFD_MAIN_PLANE,
                                      0,
                                      0,
                                      0,
                                      0};

  if (!(deviceContext = GetDC(window))) {
    Close();
    MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  if (!(PixelFormat = ChoosePixelFormat(deviceContext, &pfd))) {
    Close();
    MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  if (!SetPixelFormat(deviceContext, PixelFormat, &pfd)) {
    Close();
    MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  if (!(glContext = wglCreateContext(deviceContext))) {
    Close();
    MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  if (!wglMakeCurrent(deviceContext, glContext)) {
    Close();
    MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  ShowWindow(window, SW_SHOW);
  SetForegroundWindow(window);
  SetFocus(window);
  _resizer->Resize(_width, _height);

  if (!_initializer->Initialize()) {
    Close();
    MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  return true;
#endif
  return false;
}

void Window::Close() {
#if defined USE_GLX
  if (_fullscreen) {
#if defined HAVE_XF86VIDMODE
    XF86VidModeSwitchToMode(display, screen, &vidMode);
    XF86VidModeSetViewPort(display, screen, 0, 0);
#endif
  }

  if (hRC) {
    if (!glXMakeCurrent(display, None, NULL)) {
      printf("Could not release drawing context.\n");
    }
    glXDestroyContext(display, hRC);
    hRC = NULL;
  }

  XCloseDisplay(display);
#elif defined USE_AGL
  if (!_fullscreen) {
    aglSetCurrentContext(NULL);
    aglDestroyContext(_aglContext);
    _aglContext = NULL;
  }
#elif defined USE_CGL
#error unimplemented method
#elif defined USE_WGL
  if (_fullscreen) {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(true);
  }

  if (glContext) {
    if (!wglMakeCurrent(NULL, NULL))
      MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    if (!wglDeleteContext(glContext))
      MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    glContext = NULL;
  }

  if (deviceContext && !ReleaseDC(window, deviceContext)) {
    MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    deviceContext = NULL;
  }

  if (window && !DestroyWindow(window)) {
    MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    window = NULL;
  }

  if (!UnregisterClass("OpenArena v0.1.0", instance)) {
    MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    instance = NULL;
  }
#endif
}

bool Window::Open(string title, int width, int height, int bits, bool fullscreenflag) {
  _fullscreen = fullscreenflag;
  _width = width;
  _height = height;
  _colorDepth = bits;
  _name = title;

  return Open();
}

Window::Window() {
  _initializer = new Initializer();
  _resizer = new Resizer();
}

Window::~Window() {}

void Window::SetInitializer(Window::Initializer* initializer) {
  _initializer = initializer;
}

void Window::SetResizer(Window::Resizer* resizer) {
  _resizer = resizer;
}

void Window::Resizer::Resize(uint32_t width, uint32_t height) {
  if (height == 0) height = 1;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int Window::Initializer::Initialize() {
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

void Window::Resize(uint32_t width, uint32_t height) {
  _resizer->Resize(width, height);
}

Vec2i Window::GetMousePosition() {
#ifdef USE_GLX
  ::Window rootWindow;
  ::Window childWindow;
  int rootX;
  int rootY;
  int mouseX;
  int mouseY;
  unsigned int mask;
  if (!XQueryPointer(display, window, &rootWindow, &childWindow, &rootX, &rootY, &mouseX, &mouseY, &mask)) {
    return Vec2i(-1, -1);
  } else {
    return Vec2i(mouseX, mouseY);
  }
#elif defined USE_AGL
#warning unimplemented method
#elif defined USE_CGL
#error unimplemented method
#elif defined USE_WGL
  POINT pos;
  GetCursorPos(&pos);
  return Vec2i(pos.x, pos.y);
#else
  return Vec2i(0, 0);
#endif
}

void Window::SetMousePosition(Vec2i pos) {
#if defined USE_GLX
  XWarpPointer(display, None, window, 0, 0, 0, 0, pos.x, pos.y);
#elif defined USE_AGL
#warning unimplemented method
#elif defined USE_CGL
#error unimplemented method
#elif defined USE_WGL
  SetCursorPos(pos.x, pos.y);
#endif
}

#ifdef USE_GLX
Display* Window::GetDisplay() {
  return display;
}

Cursor Window::CreateWindowedCursor() {
  return CreateFullscreenCursor();
}

Cursor OpenArena::Window::CreateFullscreenCursor() {
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

}  // End namespace OpenGL
}  // End namespace OpenArena
