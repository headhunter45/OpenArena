#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "camera.h"
#include "ctrls.h"

namespace OpenArena
{
	class Player
	{
	public:
		void Load();
		void Save();
		void CreateCharacter();
		//void FirePrimary(ENTITY& ent);
		//void FireSecondary();
		void AddItem(unsigned int item);
		void RemoveItem(unsigned int item);
		
		ControlSchemeClass controls;
		Camera camera;
		
		
	private:
		
	};
};
#endif
