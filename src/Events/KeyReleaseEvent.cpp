#include "KeyReleaseEvent.h"
#include <cstdio>
#include "../main.h"
namespace OpenArena
{
	namespace Events
	{
		KeyReleaseEvent::KeyReleaseEvent(OpenArena::Keys key)
		{
			_key = key;
			SetEventType(KeyReleaseEventType);
		}
		
		KeyReleaseEvent::~KeyReleaseEvent()
		{
		}
		
		OpenArena::Keys KeyReleaseEvent::GetKey()
		{
			return _key;
		}
		bool KeyReleaseEvent::KeyReleaseEventHandler::Handles(Event::EventType type)
		{
			if(type == Event::KeyReleaseEventType)
			{
				return true;
			}
			return false;
		}
				
		void KeyReleaseEvent::KeyReleaseEventHandler::HandleEvent(Event* event)
		{
			if(event != 0x0)
			{
				if(event->GetEventType() == Event::KeyReleaseEventType)
				{
					KeyReleaseEvent* ev = (KeyReleaseEvent*) event;
					printf("KeyReleased: %s\n", GetKeyName(ev->GetKey()));
					keys[ev->GetKey()] = false;
					keys2[ev->GetKey()] = false;
				}
			}
		}
		
		/*
		void KeyReleaseEvent::KeyReleaseEventHandler::HandleEvent(Event event)
		{
			if(event.GetEventType() == Event::KeyReleaseEventType)
			{
				KeyReleaseEvent ev = *((KeyReleaseEvent*)&event);
				printf("KeyReleased: %s\n", GetKeyName(ev.GetKey()));
				keys[ev.GetKey()] = false;
				keys2[ev.GetKey()] = false;
			}
		}
		*/
		
		KeyReleaseEvent::KeyReleaseEventHandler::KeyReleaseEventHandler()
		{
		}
		
		KeyReleaseEvent::KeyReleaseEventHandler::~KeyReleaseEventHandler()
		{
		}
		
	};
};
