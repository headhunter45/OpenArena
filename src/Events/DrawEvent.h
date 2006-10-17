#ifndef __OpenArena_DrawEvent_h__
#define __OpenArena_DrawEvent_h__

#include "Event.h"
#include "../Geometry2D/Rectangle.h"
#include "../level.h"

namespace OpenArena
{
	namespace Events
	{
		class DrawEvent :public OpenArena::Events::Event
		{
		public:
			class DrawEventHandler :public EventHandler
			{
			public:
				DrawEventHandler(Level* level);
				virtual bool Handles(EventType type);
				virtual void HandleEvent(Event* event);
				//virtual void HandleEvent(Event event);
			private:
				Level* _level;		
			};
			
			DrawEvent();
			virtual ~DrawEvent();
		};
	};
};

#endif //__OpenArena_DrawEvent_h__
