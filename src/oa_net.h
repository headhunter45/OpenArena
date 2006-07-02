#ifndef __oa_net_h__
#define __oa_net_h__

//NO REAL work is done by _init or _fini they should just call
//	Init and DeInit instead.
void _init();
void _fini();
void Init();
void DeInit();

namespace OpenArena
{
	namespace Net
	{
	};
};

#endif
