//Yank/rename these maybe MapEntities
using namespace std;
using OpenArena::Vec3d;

/*!
 * \brief
 * Write brief comment for LIGHT here.
 * 
 * Write detailed description for LIGHT here.
 * 
 * \remarks
 * Write remarks for LIGHT here.
 * 
 * \see
 * Separate items with the '|' character.
 */
struct LIGHT
{
	GLfloat coords[4];
	GLfloat color[4];
};

/*!
 * \brief
 * Write brief comment for PLAYER_START here.
 * 
 * Write detailed description for PLAYER_START here.
 * 
 * \remarks
 * Write remarks for PLAYER_START here.
 * 
 * \see
 * Separate items with the '|' character.
 */
struct PLAYER_START
{
	Vec3d coords;
	Vec3d heading;
};
/*!
 * \brief
 * Write brief comment for PLAYER_DEATHMATCH_START here.
 * 
 * Write detailed description for PLAYER_DEATHMATCH_START here.
 * 
 * \remarks
 * Write remarks for PLAYER_DEATHMATCH_START here.
 * 
 * \see
 * Separate items with the '|' character.
 */
struct PLAYER_DEATHMATCH_START
{
	Vec3d coords;
	Vec3d heading;
};
/*!
 * \brief
 * Write brief comment for BOT_START here.
 * 
 * Write detailed description for BOT_START here.
 * 
 * \remarks
 * Write remarks for BOT_START here.
 * 
 * \see
 * Separate items with the '|' character.
 */
struct BOT_START
{
	Vec3d coords;
	Vec3d heading;
	string name;
};
/*!
 * \brief
 * Write brief comment for GEOMETRY here.
 * 
 * Write detailed description for GEOMETRY here.
 * 
 * \remarks
 * Write remarks for GEOMETRY here.
 * 
 * \see
 * Separate items with the '|' character.
 */
struct GEOMETRY
{
	int x;
};
/*!
 * \brief
 * Write brief comment for PROJECTILE here.
 * 
 * Write detailed description for PROJECTILE here.
 * 
 * \remarks
 * Write remarks for PROJECTILE here.
 * 
 * \see
 * Separate items with the '|' character.
 */
struct PROJECTILE
{
	Vec3d heading;
	Vec3d start;
	Vec3d end;
	int dammage;
	float creation;
	
};
//const PROJECTILE BULLET = {{0,0,0},{0,0,0},{0,0,0},5};
//const PROJECTILE SPIKE = {{0,0,0},{0,0,0},{0,0,0},10};

/*!
 * \brief
 * Write brief comment for ENTITY here.
 * 
 * Write detailed description for ENTITY here.
 * 
 * \remarks
 * Write remarks for ENTITY here.
 * 
 * \see
 * Separate items with the '|' character.
 */
struct ENTITY
{
	PLAYER_START* Player_Start;
	int numPlayer_Start;
	PLAYER_DEATHMATCH_START* Player_Deathmatch_Start;
	int numPlayer_Deathmatch_Start;
	BOT_START* Bot_Start;
	int numBot_Start;
	GEOMETRY* Geometry;
	int numGeometry;
	PROJECTILE* Projectile;
	int numProjectile;
	
	/*!
	 * \brief
	 * Write brief comment for ENTITY here.
	 * 
	 * \throws <exception class>
	 * Description of criteria for throwing this exception.
	 * 
	 * Write detailed description for ENTITY here.
	 * 
	 * \remarks
	 * Write remarks for ENTITY here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	ENTITY();

};

enum ITEM_TYPE{/*all weapons go first*/WEAPON_LASERPISTOL = 1, WEAPON_SHOTGUN = 2, ITEM_BANDAGES = 4,  RUNE_DAMMAGEMULTIPLIER = 8, RUNE_PROTECTION = 16, RUNE_VAMPIRE = 32, RUNE_SPEED = 64, RUNE_DOC = 128};//This semicolon got rid of 107 errors and no warnings
