#ifndef __OpenArena_Object_h__
#define __OpenArena_Object_h__

namespace OpenArena
{
	class Object
	{
	public:
		Object();
		virtual ~Object();
		virtual const char* GetClassName();
	};
};

#endif //__OpenArena_Object_h__