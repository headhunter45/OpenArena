#ifndef __vector_h__
#define __vector_h__

#include <cmath>
namespace OpenArena{
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

	class Vec2i
	{
	public:
		int x,y;
		Vec2i();	//Default Constructor
		Vec2i(const Vec2i&);	//Copy Constructor
		Vec2i(int);  // from an angle
		Vec2i(int,int);	//from values

		int lengthsquared() const;
		int length() const;
		void normalize();
		Vec2i normalized() const;

		Vec2i cross(const Vec2i&) const;
		Vec2i operator=(const Vec2i&);
		Vec2i operator*(const Vec2i&) const;
		Vec2i operator+(const Vec2i&) const;
		Vec2i operator-(const Vec2i&) const;
		//Vec2i operator/(const Vec2i&) const;	//Is this right?
		Vec2i operator*(int) const;
		Vec2i operator/(int) const;
		bool operator==(const Vec2i&) const;
		bool operator!=(const Vec2i&) const;
	};
};
#endif
