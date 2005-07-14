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

#include "../include/camera.h"

namespace OpenArena
{
	Camera::Camera()
	{
		m_vPosition = Vec3f(0,0,0);
		m_vView = Vec3f(0,0,-1);
		m_vUpVector = Vec3f(0,1,0);
	}
	
	void Camera::PositionCamera(double xpos,  double ypos,  double zpos,
									 double xview, double yview, double zview,
									 double xup,	  double yup,   double zup)
	{
		m_vPosition = Vec3f(xpos, ypos, zpos);
		m_vView = Vec3f(xview, yview, zview);
		m_vUpVector = Vec3f(xup, yup, zup);
	}
	
	void Camera::PositionCamera(Vec3f pos, Vec3f view, Vec3f up)
	{
		m_vPosition = pos;
		m_vView = view;
		m_vUpVector = up;
	}
	
	void Camera::SetViewByMouse(Window window)
	{
		//Remove the ifdef and use the linux section for both linux and windows
		#ifdef __linux
		static double currentRotX = 0.0f;
		Vec2i pos;
		Vec2i middle;
		double angleZ;
		
		middle.x = window.width/2;
		middle.y = window.height/2;
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
				Vec3d axis = (m_vView - m_vPosition).cross(m_vUpVector);
				axis.normalize();
				RotateView(angleZ, axis.x, axis.y, axis.z);
				RotateView((middle.x-pos.x)/1000.0, 0, 1, 0);
				//RotateView((middle.x-pos.x)/1000.0, m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
			}
		}		
		#endif
		//Most of this is sorta right for linux I think but since I don't know how yet it's currently windows only
		#ifdef WIN32
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
				Vec3f axis = (m_vView - m_vPosition).cross(m_vUpVector);
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
		Vec3f heading = (m_vView - m_vPosition).normalized();
		
		m_vPosition.x += heading.x * speed;
		m_vPosition.z += heading.z * speed;
		m_vView.x += heading.x * speed;
		m_vView.z += heading.z * speed;
	}
	
	void Camera::RotateView(double angle, Vec3d axis)
	{
		//Maybe make this not call the other RotateView later
		axis.normalize();
		RotateView(angle, axis.x, axis.y, axis.z);
	}
	
	void Camera::RotateView(double angle, double x, double y, double z)
	{
		Vec3f nView;
		Vec3f cView;
	
		cView = m_vView - m_vPosition;
	
		double cosTheta = cos(angle);
		double sinTheta = sin(angle);
	
		nView.x = (cosTheta + (1 - cosTheta) * x * x) * cView.x +
				  ((1 - cosTheta) * x * y - z * sinTheta) * cView.y +
				  ((1 - cosTheta) * x * z + y * sinTheta) * cView.z;
	
		nView.y = (cosTheta + (1 - cosTheta) * y * y) * cView.y +
				  ((1- cosTheta) * x * y + z * sinTheta) * cView.x + 
				  ((1 - cosTheta) * y * z - x * sinTheta) * cView.z;
	
		nView.z = (cosTheta + (1 - cosTheta) * z * z) * cView.z+
				  ((1 - cosTheta) * x * z - y * sinTheta) * cView.x +
				  ((1 - cosTheta) * y * z + x * sinTheta) * cView.y;
		
		m_vView.x = m_vPosition.x + nView.x;	  
		m_vView.y = m_vPosition.y + nView.y;
		m_vView.z = m_vPosition.z + nView.z;
	}
	
	void Camera::StrafeCamera(double speed)
	{
		m_vPosition.x += m_vStrafe.x * speed;
		m_vPosition.z += m_vStrafe.z * speed;
		m_vView.x += m_vStrafe.x * speed;
		m_vView.z += m_vStrafe.z * speed;
	}
	
	
	
	void Camera::Update()
	{
		m_vStrafe =((m_vView - m_vPosition).cross(m_vUpVector)).normalized();
		//SetViewByMouse();	//TODO take this whole function out asap
	
	}
	
	void Camera::Look()
	{
		gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z,
				  m_vView.x,	 m_vView.y,		m_vView.z,
				  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
	}
	
	Vec3f Camera::Position()
	{
		return m_vPosition;
	}
	
	Vec3f Camera::Strafe()
	{
		return m_vStrafe;
	}
	
	Vec3f Camera::UpVector()
	{
		return m_vUpVector;
	}
	
	Vec3f Camera::View()
	{
		return m_vView;
	}
};
