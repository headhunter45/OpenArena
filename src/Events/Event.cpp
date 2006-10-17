#include "Event.h"

namespace OpenArena
{
	namespace Events
	{
		Event::Event()
		{
			SetEventType(UnknownEventType);
		}
		
		Event::~Event()
		{
		}
		
		OpenArena::Events::Event::EventType Event::GetEventType()
		{
			return _type;
		}
		
		void Event::SetEventType(OpenArena::Events::Event::EventType type)
		{
			_type = type;
		}
		
		Event::EventHandler::EventHandler()
		{
		}
		
		Event::EventHandler::~EventHandler()
		{
		}
		
		bool Event::EventHandler::Handles(Event::EventType eventType)
		{
			return false;
		}
		
		void Event::EventHandler::HandleEvent(Event* event)
		{
		}		

		/*
		void Event::EventHandler::HandleEvent(Event event)
		{
		}
		*/		
	}
}
