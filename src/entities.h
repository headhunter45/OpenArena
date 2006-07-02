//Yank/rename these maybe MapEntities
using namespace std;
using OpenArena::Vec3d;

struct LIGHT
{
	GLfloat coords[4];
	GLfloat color[4];
};

struct PLAYER_START
{
	Vec3d coords;
	Vec3d heading;
};
struct PLAYER_DEATHMATCH_START
{
	Vec3d coords;
	Vec3d heading;
};
struct BOT_START
{
	Vec3d coords;
	Vec3d heading;
	string name;
};
struct GEOMETRY
{
	int x;
};
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
	
	ENTITY(); 

};

enum ITEM_TYPE{/*all weapons go first*/WEAPON_LASERPISTOL = 1, WEAPON_SHOTGUN = 2, ITEM_BANDAGES = 4,  RUNE_DAMMAGEMULTIPLIER = 8, RUNE_PROTECTION = 16, RUNE_VAMPIRE = 32, RUNE_SPEED = 64, RUNE_DOC = 128};//This semicolon got rid of 107 errors and no warnings