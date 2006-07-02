#include "vector.h"
#include "myglTexture.h"

namespace OpenArena
{
	class Triangle
	{
	public:
		Texture texture;
		uint32 texID;
		Vec3f vertecies[3];
		Vec2f texCoords[3];
		Vec3f normal;
	};
};
