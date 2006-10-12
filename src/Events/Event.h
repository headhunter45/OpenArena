#ifndef __OpenArena_Event_h__
#define __OpenArena_Event_h__

namespace OpenArena
{
	class Event
	{
	public:
		enum EventType
		{
			InputEventType,
			DrawEventType
		};

		class EventHandler
		{
		public:
			virtual bool Handles(Event::EventType eventType) = 0;
			virtual void HandleEvent(Event* event) = 0;
//			virtual ~EventHandler(){};
		};
		
		virtual EventType GetEventType() = 0;
		
		//remove this
		Event(){};
		virtual ~Event(){};
	};
};
#endif //__OpenArena_Event_h__
