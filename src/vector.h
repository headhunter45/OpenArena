/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks   *
 *   tomhicks@cse.buffalo.edu   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef __vector_h__
#define __vector_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include <cmath>
namespace OpenArena{
	/*!
	 * \brief
	 * Write brief comment for Vec3d here.
	 * 
	 * Write detailed description for Vec3d here.
	 * 
	 * \remarks
	 * Write remarks for Vec3d here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Vec3d
	{
	public:
		double x,y,z;
		/*!
		 * \brief
		 * Write brief comment for Vec3d here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec3d here.
		 * 
		 * \remarks
		 * Write remarks for Vec3d here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d();	//Default Constructor
		/*!
		 * \brief
		 * Write brief comment for Vec3d here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec3d here.
		 * 
		 * \remarks
		 * Write remarks for Vec3d here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d(const Vec3d&);	//Copy Constructor
		/*!
		 * \brief
		 * Write brief comment for Vec3d here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec3d here.
		 * 
		 * \remarks
		 * Write remarks for Vec3d here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d(double, double);	//From an angle
		/*!
		 * \brief
		 * Write brief comment for Vec3d here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec3d here.
		 * 
		 * \remarks
		 * Write remarks for Vec3d here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d(double, double, double);	//From values
		/*!
		 * \brief
		 * Write brief comment for lengthsquared here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for lengthsquared here.
		 * 
		 * \remarks
		 * Write remarks for lengthsquared here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		double lengthsquared() const;
		/*!
		 * \brief
		 * Write brief comment for length here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for length here.
		 * 
		 * \remarks
		 * Write remarks for length here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		double length() const;
		/*!
		 * \brief
		 * Write brief comment for normalize here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for normalize here.
		 * 
		 * \remarks
		 * Write remarks for normalize here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void normalize();
		/*!
		 * \brief
		 * Write brief comment for normalized here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for normalized here.
		 * 
		 * \remarks
		 * Write remarks for normalized here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d normalized() const;

		/*!
		 * \brief
		 * Write brief comment for cross here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for cross here.
		 * 
		 * \remarks
		 * Write remarks for cross here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d cross(const Vec3d&) const;
		/*!
		 * \brief
		 * Write brief comment for operator = here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator = here.
		 * 
		 * \remarks
		 * Write remarks for operator = here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void  operator=(const Vec3d&);
		/*!
		 * \brief
		 * Write brief comment for operator * here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator * here.
		 * 
		 * \remarks
		 * Write remarks for operator * here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d operator*(const Vec3d&) const;
		/*!
		 * \brief
		 * Write brief comment for operator + here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator + here.
		 * 
		 * \remarks
		 * Write remarks for operator + here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d operator+(const Vec3d&) const;
		/*!
		 * \brief
		 * Write brief comment for operator - here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator - here.
		 * 
		 * \remarks
		 * Write remarks for operator - here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d operator-(const Vec3d&) const;
		/*!
		 * \brief
		 * Write brief comment for operator * here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator * here.
		 * 
		 * \remarks
		 * Write remarks for operator * here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d operator*(double) const;
		/*!
		 * \brief
		 * Write brief comment for operator / here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator / here.
		 * 
		 * \remarks
		 * Write remarks for operator / here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3d operator/(double) const;

	};

	/*!
	 * \brief
	 * Write brief comment for Vector here.
	 * 
	 * \param 
	 * Description of parameter .
	 * 
	 * \param 
	 * Description of parameter .
	 * 
	 * \returns
	 * Write description of return value here.
	 * 
	 * \throws <exception class>
	 * Description of criteria for throwing this exception.
	 * 
	 * Write detailed description for Vector here.
	 * 
	 * \remarks
	 * Write remarks for Vector here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	Vec3d Vector(double, double);
	//Vec3d Angle2Vec3f()
	/*!
	 * \brief
	 * Write brief comment for Vec2f here.
	 * 
	 * Write detailed description for Vec2f here.
	 * 
	 * \remarks
	 * Write remarks for Vec2f here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Vec2f 
	{
	public:
		float x,y;
		/*!
		 * \brief
		 * Write brief comment for Vec2f here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2f here.
		 * 
		 * \remarks
		 * Write remarks for Vec2f here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f();	//Default Constructor
		/*!
		 * \brief
		 * Write brief comment for Vec2f here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2f here.
		 * 
		 * \remarks
		 * Write remarks for Vec2f here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f(const Vec2f&);	//Copy Constructor
		/*!
		 * \brief
		 * Write brief comment for Vec2f here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2f here.
		 * 
		 * \remarks
		 * Write remarks for Vec2f here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f(double);  // from an angle
		/*!
		 * \brief
		 * Write brief comment for Vec2f here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2f here.
		 * 
		 * \remarks
		 * Write remarks for Vec2f here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f(double, double);	//from values

		/*!
		 * \brief
		 * Write brief comment for lengthsquared here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for lengthsquared here.
		 * 
		 * \remarks
		 * Write remarks for lengthsquared here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		double lengthsquared() const;
		/*!
		 * \brief
		 * Write brief comment for length here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for length here.
		 * 
		 * \remarks
		 * Write remarks for length here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		double length() const;
		void normalize();
		/*!
		 * \brief
		 * Write brief comment for normalized here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for normalized here.
		 * 
		 * \remarks
		 * Write remarks for normalized here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f normalized() const;

		/*!
		 * \brief
		 * Write brief comment for cross here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for cross here.
		 * 
		 * \remarks
		 * Write remarks for cross here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f cross(const Vec2f&) const;
		/*!
		 * \brief
		 * Write brief comment for operator = here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator = here.
		 * 
		 * \remarks
		 * Write remarks for operator = here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f operator=(const Vec2f&);
		/*!
		 * \brief
		 * Write brief comment for operator * here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator * here.
		 * 
		 * \remarks
		 * Write remarks for operator * here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f operator*(const Vec2f&) const;
		/*!
		 * \brief
		 * Write brief comment for operator + here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator + here.
		 * 
		 * \remarks
		 * Write remarks for operator + here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f operator+(const Vec2f&) const;
		/*!
		 * \brief
		 * Write brief comment for operator - here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator - here.
		 * 
		 * \remarks
		 * Write remarks for operator - here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f operator-(const Vec2f&) const;
		//Vec2f operator/(const Vec2f&) const;	//Is this right?
		/*!
		 * \brief
		 * Write brief comment for operator * here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator * here.
		 * 
		 * \remarks
		 * Write remarks for operator * here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f operator*(double) const;
		/*!
		 * \brief
		 * Write brief comment for operator / here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator / here.
		 * 
		 * \remarks
		 * Write remarks for operator / here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2f operator/(double) const;
	};

	typedef Vec3d Vec3f;

	/*!
	 * \brief
	 * Write brief comment for Vec2i here.
	 * 
	 * Write detailed description for Vec2i here.
	 * 
	 * \remarks
	 * Write remarks for Vec2i here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Vec2i
	{
	public:
		int x,y;
		/*!
		 * \brief
		 * Write brief comment for Vec2i here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2i here.
		 * 
		 * \remarks
		 * Write remarks for Vec2i here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i();	//Default Constructor
		/*!
		 * \brief
		 * Write brief comment for Vec2i here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2i here.
		 * 
		 * \remarks
		 * Write remarks for Vec2i here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		/*!
		 * \brief
		 * Write brief comment for Vec2i here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2i here.
		 * 
		 * \remarks
		 * Write remarks for Vec2i here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i(const Vec2i&);	//Copy Constructor
		Vec2i(int);  // from an angle
		/*!
		 * \brief
		 * Write brief comment for Vec2i here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Vec2i here.
		 * 
		 * \remarks
		 * Write remarks for Vec2i here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i(int,int);	//from values

		/*!
		 * \brief
		 * Write brief comment for lengthsquared here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for lengthsquared here.
		 * 
		 * \remarks
		 * Write remarks for lengthsquared here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		int lengthsquared() const;
		/*!
		 * \brief
		 * Write brief comment for length here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for length here.
		 * 
		 * \remarks
		 * Write remarks for length here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		int length() const;
		/*!
		 * \brief
		 * Write brief comment for normalize here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for normalize here.
		 * 
		 * \remarks
		 * Write remarks for normalize here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void normalize();
		/*!
		 * \brief
		 * Write brief comment for normalized here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for normalized here.
		 * 
		 * \remarks
		 * Write remarks for normalized here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i normalized() const;

		/*!
		 * \brief
		 * Write brief comment for cross here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for cross here.
		 * 
		 * \remarks
		 * Write remarks for cross here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i cross(const Vec2i&) const;
		/*!
		 * \brief
		 * Write brief comment for operator = here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator = here.
		 * 
		 * \remarks
		 * Write remarks for operator = here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i operator=(const Vec2i&);
		/*!
		 * \brief
		 * Write brief comment for operator * here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator * here.
		 * 
		 * \remarks
		 * Write remarks for operator * here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i operator*(const Vec2i&) const;
		/*!
		 * \brief
		 * Write brief comment for operator + here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator + here.
		 * 
		 * \remarks
		 * Write remarks for operator + here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i operator+(const Vec2i&) const;
		/*!
		 * \brief
		 * Write brief comment for operator - here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator - here.
		 * 
		 * \remarks
		 * Write remarks for operator - here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i operator-(const Vec2i&) const;
		//Vec2i operator/(const Vec2i&) const;	//Is this right?
		/*!
		 * \brief
		 * Write brief comment for operator * here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator * here.
		 * 
		 * \remarks
		 * Write remarks for operator * here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i operator*(int) const;
		/*!
		 * \brief
		 * Write brief comment for operator / here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator / here.
		 * 
		 * \remarks
		 * Write remarks for operator / here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec2i operator/(int) const;
		/*!
		 * \brief
		 * Write brief comment for operator == here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator == here.
		 * 
		 * \remarks
		 * Write remarks for operator == here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator==(const Vec2i&) const;
		/*!
		 * \brief
		 * Write brief comment for operator != here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for operator != here.
		 * 
		 * \remarks
		 * Write remarks for operator != here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator!=(const Vec2i&) const;
	};
};
#endif
