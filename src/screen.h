#ifndef __screen_h__
#define __screen_h__
#include <string>

using namespace std;
namespace OpenArena
{
	class Screen
	{
	public:
		Screen();
		int GetWidth();
		int GetHeight();
		int GetColorDepth();
		bool GetFullscreen();
		const char* GetName();
		void SetWidth(int);
		void SetHeight(int);
		void Resize(int, int);
		void SetColorDepth(int);
		void SetFullscreen(bool);
		void ToggleFullscreen();
		void SetName(const char*);
		void SetName(string);
	protected:
		short _width;
		short _height;
		char _colorDepth;
		bool _fullscreen;
//	public:
		string _name;
	};
};
#endif
