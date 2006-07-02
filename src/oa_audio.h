#ifndef __oa_audio_h__
#define __oa_audio_h__

#include "vector.h"

//NO REAL work is done by _init or _fini they should just call
//	Init and DeInit instead.
void _init();
void _fini();
void Init();
void DeInit();

namespace OpenArena
{
	namespace Audio
	{
		class Stream
		{
			Stream();
			Stream(const char* filename);
			bool Load(const char* filename);
			void UnLoad();
			bool Play();
			bool Play3D();
			SetPosition(Vec3d position);
			Vec3d GetPosition();
		};
	};
};

#endif
