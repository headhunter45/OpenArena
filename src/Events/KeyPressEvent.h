#ifndef __OpenArena_KeyPressEvent_h__
#define __OpenArena_KeyPressEvent_h__
#include "Event.h"
#include "../keys.h"

namespace OpenArena
{
	namespace Events
	{
		class KeyPressEvent :public Event
		{
		public:
			KeyPressEvent(OpenArena::Keys key);
			~KeyPressEvent();
			virtual OpenArena::Keys KeyPressEvent::GetKey();
			
			class KeyPressEventHandler :public Event::EventHandler
			{
			public:
				KeyPressEventHandler();
				virtual bool Handles(Event::EventType eventType);
				virtual void HandleEvent(Event* event);
				//virtual void HandleEvent(Event event);
				virtual ~KeyPressEventHandler();
			};
		
		private:
			OpenArena::Keys _key;			
		};
	};
};

#endif // __OpenArena_KeyPressEvent_h__