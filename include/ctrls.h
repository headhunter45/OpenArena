#include "physics.h"
#include "datatypes.h"
#include "list.h"
#include <windows.h>

class ControlSchemeClass
{
public:
	void LoadDefaultControlScheme();
	void ClearControlScheme();
	void Unbind(uint8);

	list<uint8> forward;
	list<uint8> backward;
	list<uint8> lookLeft;
	list<uint8> lookRight;
	list<uint8> lookUp;
	list<uint8> lookDown;
	list<uint8> moveLeft;
	list<uint8> moveRight;
	list<uint8> moveUp;
	list<uint8> moveDown;
	list<uint8> firePrimary;
	list<uint8> fireSecondary;
	list<uint8> weaponNext;
	list<uint8> weaponPrev;
	list<uint8> toggleLights;
	list<uint8> toggleFPS;
	list<uint8> toggleConsole;
	list<uint8> toggleMouseLook;
	list<uint8> quickMouseLook;
	list<uint8> rollLeft;
	list<uint8> rollRight;	
};