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
/*//This class seems to never be used and I dont' remember why I made it.
class Position
{
public:
	GLfloat xrot;			// X rotation
	GLfloat yrot;			// Y rotation
	GLfloat zrot;			// Z rotation
	GLfloat xtrans;			// X translation
	GLfloat ytrans;			// Y translation
	GLfloat ztrans;			// Z translation
	bool stepRight;		
	bool stepLeft;
	Position()
	{
		xtrans = 0.0f;
		ytrans = 0.0f;
		ztrans = 0.0f;
		xrot = 0.0f;
		yrot = 0.0f;
		zrot = 0.0f;
	}
private:

};
*/
