#ifndef __vector_h__
#define __vector_h__

#include <cmath>

class Vec3d
{
public:
	double x,y,z;
	Vec3d();	//Default Constructor
	Vec3d(const Vec3d&);	//Copy Constructor
	Vec3d(double, double);	//From an angle
	Vec3d(double, double, double);	//From values
	double lengthsquared() const;
	double length() const;
	void normalize();
	Vec3d normalized() const;
	
	Vec3d cross(const Vec3d&) const;
	void  operator=(const Vec3d&);
	Vec3d operator*(const Vec3d&) const;
	Vec3d operator+(const Vec3d&) const;
	Vec3d operator-(const Vec3d&) const;
	Vec3d operator*(double) const;
	Vec3d operator/(double) const;

};

Vec3d Vector(double, double);
//Vec3d Angle2Vec3f()
class Vec2f 
{
public:
	float x,y;
	Vec2f();	//Default Constructor
	Vec2f(const Vec2f&);	//Copy Constructor
	Vec2f(double);  // from an angle
	Vec2f(double, double);	//from values

	double lengthsquared() const;
	double length() const;
	void normalize();
	Vec2f normalized() const;
	
	Vec2f cross(const Vec2f&) const;
	Vec2f operator=(const Vec2f&);
	Vec2f operator*(const Vec2f&) const;
	Vec2f operator+(const Vec2f&) const;
	Vec2f operator-(const Vec2f&) const;
	//Vec2f operator/(const Vec2f&) const;	//Is this right?
	Vec2f operator*(double) const;
	Vec2f operator/(double) const;
};

typedef Vec3d Vec3f;

#endif
