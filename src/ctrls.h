#include "keys.h"
#include "physics.h"
#include "datatypes.h"
#include "list.h"

namespace OpenArena{
	/*!
	 * \brief
	 * Write brief comment for ControlScheme here.
	 * 
	 * Write detailed description for ControlScheme here.
	 * 
	 * \remarks
	 * Write remarks for ControlScheme here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class ControlScheme
	{
	public:
		enum Action{ACTION_FORWARD, ACTION_BACKWARD, ACTION_LOOKLEFT, ACTION_LOOKRIGHT, ACTION_LOOKUP,
		ACTION_LOOKDOWN, ACTION_MOVELEFT, ACTION_MOVERIGHT, ACTION_MOVEUP, ACTION_MOVEDOWN,
		ACTION_ROLLLEFT, ACTION_ROLLRIGHT, ACTION_FIREPRIMARY, ACTION_FIRESECONDARY,
		ACTION_WEAPONNEXT, ACTION_WEAPONPREV, ACTION_TOGGLE_LIGHTS, ACTION_TOGGLE_FPS,
		ACTION_TOGGLE_CONSOLE, ACTION_TOGGLE_MOUSELOOK, ACTION_QUICKMOUSELOOK};
		/*!
		 * \brief
		 * Write brief comment for LoadDefaultControlScheme here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for LoadDefaultControlScheme here.
		 * 
		 * \remarks
		 * Write remarks for LoadDefaultControlScheme here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void LoadDefaultControlScheme();
		/*!
		 * \brief
		 * Write brief comment for ClearControlScheme here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ClearControlScheme here.
		 * 
		 * \remarks
		 * Write remarks for ClearControlScheme here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void ClearControlScheme();
		/*!
		 * \brief
		 * Write brief comment for Unbind here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Unbind here.
		 * 
		 * \remarks
		 * Write remarks for Unbind here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Unbind(uint8);
		/*!
		 * \brief
		 * Write brief comment for Bind here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Bind here.
		 * 
		 * \remarks
		 * Write remarks for Bind here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
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
};
