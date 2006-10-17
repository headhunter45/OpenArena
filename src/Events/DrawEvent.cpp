#include "DrawEvent.h"
#include "../main.h"

namespace OpenArena
{
	namespace Events
	{
		
		DrawEvent::DrawEvent()
		{
			SetEventType(Event::DrawEventType);
		}
		
		DrawEvent::~DrawEvent()
		{
		}
		
		bool DrawEvent::DrawEventHandler::Handles(Event::EventType type)
		{
			if(type == Event::DrawEventType)
			{
				return true;
			}
		
			return false;
		}
		
		/*
		void DrawEvent::DrawEventHandler::HandleEvent(Event event)
		{
			DrawGLScene();
		}
		*/
		
		void DrawEvent::DrawEventHandler::HandleEvent(Event* event)
		{
			DrawGLScene(_level);
		}
		
		DrawEvent::DrawEventHandler::DrawEventHandler(Level* level)
		{
			_level = level;
		}
	};
};
