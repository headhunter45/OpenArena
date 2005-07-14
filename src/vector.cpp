#include "../include/vector.h"

Vec3d::Vec3d()
{
	x=0.0f;
	y=0.0f;
	z=0.0f;
}

Vec3d::Vec3d(const Vec3d& orig)
{
	operator=(orig);
}

Vec3d::Vec3d(double xr=0, double zr=0)
{
	x=(double)sin(90-xr);
	y=(double)sin(xr);
	z=(double)(y*tan(zr));
}

Vec3d::Vec3d(double X, double Y, double Z)
{
	x = X;
	y = Y;
	z = Z;
}

double Vec3d::lengthsquared()const
{
	return (x*x+y*y+z*z);
}

double Vec3d::length() const
{
	return (double)sqrt(lengthsquared());
}

void Vec3d::normalize()
{
	x/=length();
	y/=length();
	z/=length();
}

void Vec3d::operator=(const Vec3d& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vec3d Vec3d::cross(const Vec3d& v) const
{
	return Vec3d(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

Vec3d Vec3d::operator*(const Vec3d& v) const
{
	return Vec3d(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

Vec3d Vec3d::operator+(const Vec3d& v)const
{
	return Vec3d(x+v.x, y+v.y, z+v.z);
}

Vec3d Vec3d::operator*(double f) const
{
	return Vec3d(x*f, y*f, z*f);
}

Vec3d Vec3d::operator-(const Vec3d& v)const
{
	return Vec3d(x-v.x, y-v.y, z-v.z);
}

Vec3d Vec3d::operator/(double k) const
{
	return Vec3d(x/k, y/k, z/k);
}

Vec3d Vec3d::normalized() const
{
	return Vec3d(x/length(), y/length(), z/length());
}


Vec2f::Vec2f()
{
	x=0;
	y=0;
}

Vec2f::Vec2f(const Vec2f& rtOp)
{
	x=rtOp.x;
	y=rtOp.y;
}

Vec2f Vec2f::cross(const Vec2f& rtOp) const
{
	return Vec2f(y-rtOp.y, rtOp.x-x);
}

double Vec2f::length()const
{
	return sqrt(x*x+y*y);
}

double Vec2f::lengthsquared()const
{
	return (x*x+y*y);
}

void Vec2f::normalize()
{
	x/=(float)length();
	y/=(float)length();
}

Vec2f Vec2f::normalized() const
{
	return Vec2f(x/length(), y/length());
}

Vec2f Vec2f::operator*(double rtOp) const
{
	return Vec2f(x*rtOp, y*rtOp);		
}

Vec2f Vec2f::operator+(const Vec2f& rtOp) const
{
	return Vec2f(x+rtOp.x, y+rtOp.y);
}

Vec2f Vec2f::operator*(const Vec2f& rtOp) const
{
	return Vec2f(x*rtOp.x, y*rtOp.y);
}

Vec2f Vec2f::operator-(const Vec2f& rtOp) const
{
	return Vec2f(x-rtOp.x, y-rtOp.y);
}

Vec2f Vec2f::operator/(double rtOp) const
{
	return Vec2f(x/rtOp, y/rtOp);
}

Vec2f Vec2f::operator=(const Vec2f& rtOp)
{
	x=rtOp.x;
	y=rtOp.y;
	return Vec2f(x,y);
}

Vec2f::Vec2f(double X, double Y)
{
	x=(float)X;
	y=(float)Y;
}
////////////
Vec2i::Vec2i()
{
	x=0;
	y=0;
}

Vec2i::Vec2i(const Vec2i& rtOp)
{
	x=rtOp.x;
	y=rtOp.y;
}

Vec2i Vec2i::cross(const Vec2i& rtOp) const
{
	return Vec2i(y-rtOp.y, rtOp.x-x);
}

int Vec2i::length()const
{
	return (int)sqrt((float)(x*x+y*y));
}

int Vec2i::lengthsquared()const
{
	return (x*x+y*y);
}

void Vec2i::normalize()
{
	x/=length();
	y/=length();
}

Vec2i Vec2i::normalized() const
{
	return Vec2i(x/length(), y/length());
}

Vec2i Vec2i::operator*(int rtOp) const
{
	return Vec2i(x*rtOp, y*rtOp);		
}

Vec2i Vec2i::operator+(const Vec2i& rtOp) const
{
	return Vec2i(x+rtOp.x, y+rtOp.y);
}

Vec2i Vec2i::operator*(const Vec2i& rtOp) const
{
	return Vec2i(x*rtOp.x, y*rtOp.y);
}

Vec2i Vec2i::operator-(const Vec2i& rtOp) const
{
	return Vec2i(x-rtOp.x, y-rtOp.y);
}

Vec2i Vec2i::operator/(int rtOp) const
{
	return Vec2i(x/rtOp, y/rtOp);
}

Vec2i Vec2i::operator=(const Vec2i& rtOp)
{
	x=rtOp.x;
	y=rtOp.y;
	return Vec2i(x,y);
}

Vec2i::Vec2i(int X, int Y)
{
	x=X;
	y=Y;
}

bool Vec2i::operator==(const Vec2i& rtOp) const
{
	return x == rtOp.x && y == rtOp.y;
}

bool Vec2i::operator!=(const Vec2i& rtOp) const
{
	return !(x == rtOp.x && y == rtOp.y);
}
