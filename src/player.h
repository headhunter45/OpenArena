#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "camera.h"
#include "ctrls.h"

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Player here.
	 * 
	 * Write detailed description for Player here.
	 * 
	 * \remarks
	 * Write remarks for Player here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Player
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for Load here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Load here.
		 * 
		 * \remarks
		 * Write remarks for Load here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Load();
		/*!
		 * \brief
		 * Write brief comment for Save here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Save here.
		 * 
		 * \remarks
		 * Write remarks for Save here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Save();
		/*!
		 * \brief
		 * Write brief comment for CreateCharacter here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for CreateCharacter here.
		 * 
		 * \remarks
		 * Write remarks for CreateCharacter here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void CreateCharacter();
		//void FirePrimary(ENTITY& ent);
		//void FireSecondary();
		/*!
		 * \brief
		 * Write brief comment for AddItem here.
		 * 
		 * \param item
		 * Description of parameter item.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for AddItem here.
		 * 
		 * \remarks
		 * Write remarks for AddItem here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void AddItem(unsigned int item);
		/*!
		 * \brief
		 * Write brief comment for RemoveItem here.
		 * 
		 * \param item
		 * Description of parameter item.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for RemoveItem here.
		 * 
		 * \remarks
		 * Write remarks for RemoveItem here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void RemoveItem(unsigned int item);
		
		ControlScheme controls;
		Camera camera;
		
		
	private:
		
	};
};
#endif
