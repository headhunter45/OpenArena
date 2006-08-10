#include "vector.h"
#include "myglTexture.h"

namespace OpenArena
{
	class Vertex
	{
	public:
		Vec3f coordinates;
		Vec2f textureCoordinates;
	};
	
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
		Vertex vertecies[3];
//		Vec3f vertecies[3];
//		Vec2f texCoords[3];
		Vec3f normal;
	};
	
};
