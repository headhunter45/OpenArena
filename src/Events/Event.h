#ifndef __OpenArena_Event_h__
#define __OpenArena_Event_h__
#include "../Object.h"

namespace OpenArena
{
	namespace Events
	{
		class Event :public Object
		{
		public:
			enum EventType
			{
				InputEventType,
				DrawEventType,
				KeyPressEventType,
				KeyReleaseEventType,
				AxisMotionEventType,
				UnknownEventType
			};
	
			class EventHandler
			{
			public:
				EventHandler();
				virtual bool Handles(Event::EventType eventType);
				virtual void HandleEvent(Event* event);
				//virtual void HandleEvent(Event event);
				virtual ~EventHandler();
			};
			
			Event();
			virtual ~Event();
			EventType GetEventType();
		protected:
			void SetEventType(EventType type);
		private:
			EventType _type;
		};
	};
};
#endif //__OpenArena_Event_h__
