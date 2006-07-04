#include "vector.h"
#include "myglTexture.h"

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Triangle here.
	 * 
	 * Write detailed description for Triangle here.
	 * 
	 * \remarks
	 * Write remarks for Triangle here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
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
