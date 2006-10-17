#ifndef __OpenArena_KeyReleaseEvent_h__
#define __OpenArena_KeyReleaseEvent_h__
#include "Event.h"
#include "../keys.h"

namespace OpenArena
{
	namespace Events
	{
		class KeyReleaseEvent :public Event
		{
		public:
			KeyReleaseEvent(OpenArena::Keys key);
			~KeyReleaseEvent();
			virtual OpenArena::Keys KeyReleaseEvent::GetKey();
			
			class KeyReleaseEventHandler :public Event::EventHandler
			{
			public:
				KeyReleaseEventHandler();
				virtual bool Handles(Event::EventType eventType);
				virtual void HandleEvent(Event* event);
				//virtual void HandleEvent(Event event);
				virtual ~KeyReleaseEventHandler();
			};
		
		private:
			OpenArena::Keys _key;			
		};
	};
};

#endif // __OpenArena_KeyReleaseEvent_h__
