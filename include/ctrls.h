#include "keys.h"
#include "physics.h"
#include "datatypes.h"
#include "list.h"
#ifdef WIN32
//#include <windows.h> //used for VK_ keys and possibly something else.  If this file wont compile try uncommenting this.
#endif
enum {CTRLS_FORWARD, CTRLS_BACKWARD, CTRLS_LOOKLEFT, CTRLS_LOOKRIGHT, CTRLS_LOOKUP,
	  CTRLS_LOOKDOWN, CTRLS_MOVELEFT, CTRLS_MOVERIGHT, CTRLS_MOVEUP, CTRLS_MOVEDOWN,
	  CTRLS_ROLLLEFT, CTRLS_ROLLRIGHT, CTRLS_FIREPRIMARY, CTRLS_FIRESECONDARY,
	  CTRLS_WEAPONNEXT, CTRLS_WEAPONPREV, CTRLS_TOGGLE_LIGHTS, CTRLS_TOGGLE_FPS,
	  CTRLS_TOGGLE_CONSOLE, CTRLS_TOGGLE_MOUSELOOK, CTRLS_QUICKMOUSELOOK};

class ControlSchemeClass
{
public:
	void LoadDefaultControlScheme();
	void ClearControlScheme();
	void Unbind(uint8);
	bool Bind(uint32, uint8);

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
