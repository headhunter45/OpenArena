#include "DrawEvent.h"
#include "../main.h"

OpenArena::DrawEvent::DrawEvent()
{
}

OpenArena::DrawEvent::~DrawEvent()
{
}

OpenArena::Event::EventType OpenArena::DrawEvent::GetEventType()
{
	return Event::DrawEventType;
}

bool OpenArena::DrawEvent::DrawEventHandler::Handles(OpenArena::Event::EventType type)
{
	if(type == Event::DrawEventType)
	{
		return true;
	}

	return false;
}

void OpenArena::DrawEvent::DrawEventHandler::HandleEvent(OpenArena::Event* event)
{
	DrawGLScene();
}
