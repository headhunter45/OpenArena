////////////////////////////////////////////////////////////////////////////////
//
//	Module:		oa_audio.cpp
//	Author:		Tom Hicks
//	Creation:	07-21-2005
//	LastEdit:	07-21-2005
//	Editors:	Tom Hicks
//
//	Purpose:
//
//	Summary of Methods:
//
////////////////////////////////////////////////////////////////////////////////

#include "../include/oa_audio.h"

namespace OpenArena
{
	namespace Audio
	{
		Stream::Stream()
		{
		}
		
		Stream::Stream(const char* filename)
		{
		}
		
		bool Stream::Load(const char* filename)
		{
			return false;
		}
		
		void Stream::UnLoad()
		{
		}
		
		bool Stream::Play()
		{
			return false;
		}
		
		bool Stream::Play3D()
		{
			return false;
		}

		void Stream::SetPosition(Vec3d position)
		{
		}
		
		Vec3d Stream::GetPosition()
		{
			return Vec3d(0,0,0);
		}
	};
};
