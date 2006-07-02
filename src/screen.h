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
		int GetWidth() const;
		int GetHeight() const;
		int GetColorDepth() const;
		bool GetFullscreen() const;
		const char* GetName() const;
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
