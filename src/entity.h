//Yank/rename this class
#ifndef __entity_h__
#define __entity_h__

#include "datatypes.h"

enum {	//Begin entity declaration
	ENTITY_NONE=0,				//Nonexistant entity this should never be used.
	ENTITY_PLAYER_MULTI_START	//Player start position for multiplayer.
};		//End entity declaration

class ENTITY
{
public:
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