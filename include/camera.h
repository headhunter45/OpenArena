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
		//	
		
		//Camera(const Camera&);	//Copy Constructor
		//Purpose:
		//	
		
		//Observer Accessors
		Vec3f Position();
		//Purpose:
		//	
	
		Vec3f View();
		//Purpose:
		//	
	
		Vec3f UpVector();
		//Purpose:
		//	
	
		Vec3f Strafe();
		//Purpose:
		//	
	
		//Mutators
		void PositionCamera(double xpos,  double ypos,  double zpos,
							double xview, double yview, double zview,
							double xup,	  double yup,   double zup);
		//Purpose:
		//	
		
		void PositionCamera(Vec3f pos, Vec3f view, Vec3f up);
		//Purpose:
		//	
	
		void Camera::RotateView(double angle, Vec3d axis);
		//Purpose:
		//	
		
		void RotateView(double angle, double X, double Y, double Z);
		//Purpose:
		//	
	
		void SetViewByMouse(Window window);
		//Purpose:
		//	
	
		void RotateAroundPoint(Vec3f vCenter, double X, double Y, double Z);
		//Purpose:
		//	
		
		void StrafeCamera(double speed);
		//Purpose:
		//	
		
		void MoveCamera(double speed);
		//Purpose:
		//

		void Update();
		//Purpose:
		//	
	
		void Look();
		//Purpose:
		//	

	private:
		Vec3f m_vPosition;
		Vec3f m_vView;
		Vec3f m_vUpVector;
		Vec3f m_vStrafe;
	};
};

#endif
