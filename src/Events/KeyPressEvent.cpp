#include "KeyPressEvent.h"
#include <cstdio>
#include "../main.h"
namespace OpenArena
{
	namespace Events
	{
		KeyPressEvent::KeyPressEvent(OpenArena::Keys key)
		{
			printf("KeyPressEvent created");
			_key = key;
			SetEventType(KeyPressEventType);
		}
		
		KeyPressEvent::~KeyPressEvent()
		{
		}
		
		OpenArena::Keys KeyPressEvent::GetKey()
		{
			return _key;
		}
		
		bool KeyPressEvent::KeyPressEventHandler::Handles(Event::EventType eventType)
		{
			if(eventType == Event::KeyPressEventType)
			{
				return true;
			}
			
			return false;
		}
		
		void KeyPressEvent::KeyPressEventHandler::HandleEvent(Event* event)
		{
			if(event != 0x0)
			{
				if(event->GetEventType() == Event::KeyPressEventType)
				{
					KeyPressEvent* ev = (KeyPressEvent*) event;
					printf("KeyPressed: %s\n", GetKeyName(ev->GetKey()));
					keys[ev->GetKey()] = true;
				}
			}
		}
		
		/*
		void KeyPressEvent::KeyPressEventHandler::HandleEvent(Event event)
		{
			if(event.GetEventType() == Event::KeyPressEventType)
			{
				KeyPressEvent ev = *((KeyPressEvent*)&event);
				printf("KeyPressed: %s\n", GetKeyName(ev.GetKey()));
				keys[ev.GetKey()] = true;
			}
		}
		*/
		
		KeyPressEvent::KeyPressEventHandler::KeyPressEventHandler()
		{
		}
		
		KeyPressEvent::KeyPressEventHandler::~KeyPressEventHandler()
		{
		}
		
	};
};
