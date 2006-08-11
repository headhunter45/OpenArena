////////////////////////////////////////////////////////////////////////////////
//
//	Module:		camera.cpp
//	Author:		Tom Hicks
//	Creation:	09-01-2003
//	LastEdit:	10-09-2003
//	Editors:	Tom Hicks
//
//	Purpose:
//		To implement an OpenGL Camera
//
//	Summary of Methods:
//	Camera
//		-Camera();
//			Initalize PDM's.  Sets position to 0,0,0 up to 0,1,0 and view to 0,0,-1
//		-Vec3f Position();
//			Returns a copy of the position vector.
//		-Vec3f View();
//			Returns a copy of the view vector.
//		-Vec3f UpVector();
//			Returns a copy of the up vector.
//		-Vec3f Strafe();
//			Returns a copy of the strafe vector.
//		-void PositionCamera(double xpos,  double ypos,  double zpos,
//							double xview, double yview, double zview,
//							double xup,	  double yup,   double zup);
//			Sets the position, up, and view vectors to those created from the respective input values.
//		-void PositionCamera(Vec3f pos, Vec3f view, Vec3f up);
//			Sets the position, up, and view vectors to those passed in.
//		-void RotateView(double angle, double X, double Y, double Z);
//			Rotates the view angle degrees on the axis specified by X, Y, and Z.
//		-void SetViewByMouse(Screen g_Screen);
//			Rotates the pitch and yaw of the view based on the mouse.
//		-void RotateAroundPoint(double angle, double X, double Y, double Z, Vec3f vCenter);
//			Rotates the view angle degrees around a point vCenter on the axis specified by X, Y, Z.
//		-void StrafeCamera(double speed);
//			Moves the camera along an axis perpendicular to the plane specified by the up and view vectors a distance specified by speed.
//		-void MoveCamera(double speed);
//			Moves the camera along the axis specified by it's view vector a distance equal to speed.
//		-void Update();
//			Update the internal strafe vector.
//		-void Look();
//			Positions the current viewport at point of the camera and facing the same direction.
//
////////////////////////////////////////////////////////////////////////////////

#include "camera.h"

namespace OpenArena
{
	Camera::Camera()
	{
		_position = Vec3f(0,0,0);
		_heading = Vec3f(0,0,-1);
		_up = Vec3f(0,1,0);
	}
	
	void Camera::PositionCamera(double xpos,  double ypos,  double zpos,
									 double xview, double yview, double zview,
									 double xup,	  double yup,   double zup)
	{
		_position = Vec3f(xpos, ypos, zpos);
		_heading = Vec3f(xview-xpos, yview-ypos, zview-zpos);
		_up = Vec3f(xup, yup, zup).normalized();		
		UpdateVectors();
	}
	
	void Camera::PositionCamera(Vec3f pos, Vec3f view, Vec3f up)
	{
		_position = pos;
		_heading = view-pos;
		_up = up;
		UpdateVectors();
	}
	
	void Camera::SetViewByMouse(Window window)
	{
		#if defined USE_GLX
		static double currentRotX = 0.0f;
		Vec2i pos;
		Vec2i middle;
		double angleZ;
		
		middle.x = window.GetWidth()/2;
		middle.y = window.GetHeight()/2;
		pos = window.GetMousePosition();
		if(pos != middle)
		{
			window.SetMousePosition(middle);
			angleZ = (middle.y - pos.y)/1000.0;
			currentRotX-=angleZ;
			if(currentRotX >1.0)
			{
				currentRotX = 1.0;
			}
			else if(currentRotX < -1.0)
			{
				currentRotX = -1.0;
			}
			else
			{
				Vec3d axis = (_heading).cross(_up);
				axis.normalize();
				RotateView(angleZ, axis.x, axis.y, axis.z);
				RotateView((middle.x-pos.x)/1000.0, 0, 1, 0);
				//RotateView((middle.x-pos.x)/1000.0, m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
			}
		}		
		#elif defined USE_AGL
		#error unimplemented method
		#elif defined USE_CGL
		#error unimplemented method
		#elif defined USE_WGL
		static double currentRotX = 0.0f;
		POINT mpos;
		POINT middle;
		double angleZ;
		middle.x = window.GetWidth() / 2;
		middle.y = window.GetHeight() / 2;
		GetCursorPos(&mpos);
		SetCursorPos(middle.x, middle.y);							
		if(mpos.x != middle.x || mpos.y != middle.y)
		{
			angleZ = double(middle.y - mpos.y) / 1000.0f;		
			currentRotX -= angleZ;  
			
			if(currentRotX > 1.0f)
				currentRotX = 1.0f;
			else if(currentRotX < -1.0f)
				currentRotX = -1.0f;
			else
			{
				Vec3f axis = (_heading).cross(_up);
				axis.normalize();
							
				RotateView(angleZ, axis.x, axis.y, axis.z);
	
				//need to switch these two when I figure out stuff for flight
				//till then I think the first is faster
	
				RotateView(double(middle.x - mpos.x) / 1000.0f, 0, 1, 0);
				//RotateView(double(middle.x - mpos.x) / 1000.0f, m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
			}
		}
		#endif
	}
	
	void Camera::MoveCamera(double speed)
	{
		_position  = _position + _heading * speed;
		UpdateVectors();
	}
	
	void Camera::RotateView(double angle, Vec3d axis)
	{
		//Maybe make this not call the other RotateView later
		axis.normalize();
		RotateView(angle, axis.x, axis.y, axis.z);
	}
	
	void Camera::RotateView(double angle, double x, double y, double z)
	{
		double cosTheta = cos(angle);
		double sinTheta = sin(angle);
		
		double newX = (cosTheta + (1 - cosTheta) * x * x) * _heading.x +
		               ((1 - cosTheta) * x * y - z * sinTheta) * _heading.y +
		               ((1 - cosTheta) * x * z + y * sinTheta) * _heading.z;
		               
		double newY = (cosTheta + (1 - cosTheta) * y * y) * _heading.y +
		               ((1 - cosTheta) * x * y + z * sinTheta) * _heading.x +
		               ((1 - cosTheta) * y * z - x * sinTheta) * _heading.z;
		               
		double newZ = (cosTheta + (1 - cosTheta) * z * z) * _heading.z +
					  ((1 - cosTheta) * x * z - y * sinTheta) * _heading.x +
					  ((1 - cosTheta) * y * z + x * sinTheta) * _heading.y;
		
		_heading.x = newX;
		_heading.y = newY;
		_heading.z = newZ;		
	}
	
	void Camera::StrafeCamera(double speed)
	{
		_position = _position + _strafe * speed;
	}
	
	
	
	void Camera::Update()
	{
		_strafe = ((_heading).cross(_up)).normalized();
	}
	
	void Camera::Look()
	{
		Vec3f view = _position + _heading;
		gluLookAt(_position.x, _position.y, _position.z,
		          view.x, view.y, view.z,
		          _up.x, _up.y, _up.z);
	}
	
	Vec3f Camera::Position()
	{
		return _position;
	}
	
	Vec3f Camera::Strafe()
	{
		return _strafe;
	}
	
	Vec3f Camera::UpVector()
	{
		return _up;
	}
	
	Vec3f Camera::View()
	{
		return _heading + _position;
	}
	
	void Camera::RotateHorizontal(float angle)
	{
		RotateView(angle, GetUpVector());
	}

	void Camera::RotateVertical(float angle)
	{
		RotateView(angle, GetRightVector());
	}

	Vec3f Camera::GetUpVector()
	{
		return _up;
	}

	Vec3f Camera::GetRightVector()
	{
		return _strafe;
	}

	Vec3f Camera::GetForwardVector()
	{
		return _heading;
	}
	
	void Camera::UpdateVectors()
	{
	}
};
