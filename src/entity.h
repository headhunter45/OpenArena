//Yank/rename this class
#ifndef __entity_h__
#define __entity_h__

#include "datatypes.h"

enum EntityType{	//Begin entity declaration
	ENTITY_NONE=0,				//Nonexistant entity this should never be used.
	ENTITY_PLAYER_MULTI_START	//Player start position for multiplayer.
};		//End entity declaration

/*!
 * \brief
 * Write brief comment for ENTITY here.
 * 
 * Write detailed description for ENTITY here.
 * 
 * \remarks
 * Write remarks for ENTITY here.
 * 
 * \see
 * Separate items with the '|' character.
 */
class ENTITY
{
public:
	/*!
	 * \brief
	 * Write brief comment for ENTITY here.
	 * 
	 * \throws <exception class>
	 * Description of criteria for throwing this exception.
	 * 
	 * Write detailed description for ENTITY here.
	 * 
	 * \remarks
	 * Write remarks for ENTITY here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	ENTITY()
	{
		type = ENTITY_NONE;
		vPosition = Vec3f(0,0,0);
		vHeading = Vec3f(0,0,0);
		vUp = Vec3f(0,0,0);
		health = 0;
	}

	uint32 type;
	Vec3f vPosition;
	Vec3f vHeading;
	Vec3f vUp;
	uint16 health;
};

#endif
