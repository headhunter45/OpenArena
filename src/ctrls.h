#include "keys.h"
#include "datatypes.h"
#include "list.h"

namespace OpenArena{
	/*!
	 * \brief
	 * This class represents a user's control scheme.
	 * 
	 * This class manages a set of actions and their associated keys.
	 * 
	 * \remarks
	 * This could become a set of keys with associated actions.
	 * 
	 * \see
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
		 * This method loads a hard coded default control scheme.
		 * 
		 * \remarks
		 * 
		 * \see
		 */
		void LoadDefaultControlScheme();
		
		/*!
		 * \brief
		 * This method clears this control scheme so that no keys are bound to any actions.
		 * 
		 * \remarks
		 * 
		 * \see
		 */
		void ClearControlScheme();

		/*!
		 * \brief
		 * This method removes a key from all actions.
		 * 
		 * \param 
		 * The KEY_* constant for the key to unbind.
		 * 
		 * \remarks
		 * 
		 * \see
		 */
		void Unbind(uint8);
		/*!
		 * \brief
		 * This method binds a key to an action.
		 * 
		 * \param 
		 * The ACTION_* constant for the action to bind to.
		 * 
		 * \param 
		 * The KEY_* constant for the key to bind.
		 * 
		 * \returns
		 * Returns false if an invalid action is specified and true otherwise.
		 * 
		 * \remarks
		 * This unbinds the key before binding it to the new action.
		 * 
		 * \see
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
