#ifndef __camera_h__
#define __camera_h__

#include <cmath>
#ifdef WIN32
#include <windows.h>	//Currently used for mouse stuff this should be replaced by oa_input
#endif
#include "vector.h"
#include "mygl.h"
#include "screen.h"

namespace OpenArena
{
	class Camera
	{
	public:
		//Constructors
		Camera();						//Default Constructor
		//Purpose:
		//	Creates a new Camera object located at the origin, pointing at the negative z-axis with up being the positive y-axis
		
		//Camera(const Camera&);	//Copy Constructor
		//Purpose:
		//	
		
		//Observer Accessors
		Vec3f Position();
		//Purpose:
		//	Returns the position vector of this camera.
		//		This vector is the location of the camera.
	
		Vec3f View();
		//Purpose:
		//	Returns the view vector of this camera.
		//		This vector is the direction the camera is pointing.
	
		Vec3f UpVector();
		//Purpose:
		//	Returns the up vector of this camera.
		//		This vector points up in the rendered view.
	
		Vec3f Strafe();
		//Purpose:
		//	Returns the strafe vector fo this camera.
		//		This is the direction StrafeCamera will move
	
		//Mutators
		void PositionCamera(double xpos,  double ypos,  double zpos,
							double xview, double yview, double zview,
							double xup,	  double yup,   double zup);
		//Purpose:
		//	Relocates and reorientates the camera as determined by the given vector components.
		
		void PositionCamera(Vec3f pos, Vec3f view, Vec3f up);
		//Purpose:
		//	Relocates and reorientates the camera as determined by the given vectos.
	
		void Camera::RotateView(double angle, Vec3d axis);
		//Purpose:
		//	Rotates the camera by angle degrees about the axis specified by axis.
		
		void RotateView(double angle, double X, double Y, double Z);
		//Purpose:
		//	Rotates the camera by angle degrees about the axis specified by the given components.
		//		Works the same as glRotatef(angle, X, Y, Z).
	
		void SetViewByMouse(const Window* window);
		//Purpose:
		//	Updates the view Vector based on the change in mouse position since the last time it was called.
	
		//This function needs to be reimagined and better fleshed out.
		//void RotateAroundPoint(Vec3f vCenter, double X, double Y, double Z);
		//Purpose:
		//	Rotates the camera arount the point vCenter X degrees around the x-axis, Y degrees around the y-axis, and Z degrees around the z-axis in that order
		
		void StrafeCamera(double speed);
		//Purpose:
		//	Moves the camera along it's strafe vector speed units.
		
		void MoveCamera(double speed);
		//Purpose:
		//	Moves the camera along it's view vector speed units.

		void Update();
		//Purpose:
		//	Recalculates the strafe vector.
	
		void Look();
		//Purpose:
		//	Calls gluLookAt with stored values to set the scene to the camera.

	private:
		Vec3f m_vPosition;
		Vec3f m_vView;
		Vec3f m_vUpVector;
		Vec3f m_vStrafe;
	};
};

#endif
