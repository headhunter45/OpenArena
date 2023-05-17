// clang-format off
#include "../config.h"
#include "../window.h"
// clang-format on

#ifdef USE_OPENGL
namespace OpenArena {
namespace OpenGL {
class Window : public ::OpenArena::Window {
 public:
  class Resizer : public ::OpenArena::Window::Resizer {
   public:
    void Resize(uint32_t width, uint32_t height);
  };

  class Initializer : public ::OpenArena::Window::Initializer {
   public:
    int Initialize();
  };

  Window();
  virtual ~Window();
  virtual void Close();
  virtual bool Open();
  virtual bool Open(std::string title, int width, int height, int bits,
                    bool fullscreenflag);  // make that string a const char* after this works
  virtual void SetInitializer(Initializer* initializer);
  virtual void SetResizer(Resizer* resizer);
  virtual void SwapBuffers();
  virtual void Resize(uint32_t width, uint32_t height);
  virtual Vec2i GetMousePosition();
  virtual void SetMousePosition(Vec2i pos);

 private:
#ifdef USE_GLX
  Cursor CreateWindowedCursor();
  Cursor CreateFullscreenCursor();
  int screen;
  ::Window window;
  GLXContext hRC;
  XSetWindowAttributes attributes;
  bool doubleBuffered;
#if defined HAVE_XF86VIDMODE
  XF86VidModeModeInfo vidMode;
#endif
  int x, y;
  Display* display;
#elif defined USE_AGL
  AGLContext _aglContext;
  WindowRef _window;
  Rect _bounds;
#elif defined USE_WGL
  // TODO: move this to opengl/window
  HGLRC glContext;
  HWND window;
  HDC deviceContext;
  HINSTANCE instance;
#endif
  Resizer* _resizer;
  Initializer* _initializer;
};
}  // namespace OpenGL
}  // namespace OpenArena
#ifdef USE_WGL
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif
#endif
