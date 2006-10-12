#ifndef __OpenArena_DrawEvent_h__
#define __OpenArena_DrawEvent_h__

#include "Event.h"
#include "../Geometry2D/Rectangle.h"

namespace OpenArena
{
	class DrawEvent :public OpenArena::Event
	{
	public:
		class DrawEventHandler :public EventHandler
		{
			virtual bool Handles(EventType type);
			virtual void HandleEvent(Event* event);			
		};
		
		DrawEvent();
		virtual ~DrawEvent();
		virtual Event::EventType GetEventType();		
	};
};

#endif //__OpenArena_DrawEvent_h__
