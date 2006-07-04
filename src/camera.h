/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2005 by <your name/ organization here>
 */
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
	/*!
	 * \brief
	 * Write brief comment for Camera here.
	 * 
	 * Write detailed description for Camera here.
	 * 
	 * \remarks
	 * Write remarks for Camera here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Camera
	{
	public:
		/*!
		 * \brief
		 * Creates a new Camera object.
		 * 
		 * Creates a new Camera object located at the origin, pointing at the negative z-axis with up being the positive y-axis.
		 *
		 */
		Camera();						//Default Constructor
		
		//Camera(const Camera&);	//Copy Constructor
		
		/*!
		 * \brief
		 * Returns this Camera's position.
		 * 
		 * \returns
		 * This Camera's position as a Vec3d vector.
		 * 
		 * Returns this Camera's position.
		 * 
		 */
		Vec3f Position();
		
		/*!
		 * \brief
		 * Write brief comment for View here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for View here.
		 * 
		 * \remarks
		 * Write remarks for View here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3f View();
		//Purpose:
		//	Returns the view vector of this camera.
		//		This vector is the direction the camera is pointing.
	
		/*!
		 * \brief
		 * Write brief comment for UpVector here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for UpVector here.
		 * 
		 * \remarks
		 * Write remarks for UpVector here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3f UpVector();
		//Purpose:
		//	Returns the up vector of this camera.
		//		This vector points up in the rendered view.
	
		/*!
		 * \brief
		 * Write brief comment for Strafe here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Strafe here.
		 * 
		 * \remarks
		 * Write remarks for Strafe here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Vec3f Strafe();
		//Purpose:
		//	Returns the strafe vector fo this camera.
		//		This is the direction StrafeCamera will move
	
		//Mutators
		/*!
		 * \brief
		 * Write brief comment for PositionCamera here.
		 * 
		 * \param xpos
		 * Description of parameter xpos.
		 * 
		 * \param ypos
		 * Description of parameter ypos.
		 * 
		 * \param zpos
		 * Description of parameter zpos.
		 * 
		 * \param xview
		 * Description of parameter xview.
		 * 
		 * \param yview
		 * Description of parameter yview.
		 * 
		 * \param zview
		 * Description of parameter zview.
		 * 
		 * \param xup
		 * Description of parameter xup.
		 * 
		 * \param yup
		 * Description of parameter yup.
		 * 
		 * \param zup
		 * Description of parameter zup.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for PositionCamera here.
		 * 
		 * \remarks
		 * Write remarks for PositionCamera here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void PositionCamera(double xpos,  double ypos,  double zpos,
							double xview, double yview, double zview,
							double xup,	  double yup,   double zup);
		//Purpose:
		//	Relocates and reorientates the camera as determined by the given vector components.
		
		/*!
		 * \brief
		 * Write brief comment for PositionCamera here.
		 * 
		 * \param pos
		 * Description of parameter pos.
		 * 
		 * \param view
		 * Description of parameter view.
		 * 
		 * \param up
		 * Description of parameter up.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for PositionCamera here.
		 * 
		 * \remarks
		 * Write remarks for PositionCamera here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void PositionCamera(Vec3f pos, Vec3f view, Vec3f up);
		//Purpose:
		//	Relocates and reorientates the camera as determined by the given vectos.
	
		/*!
		 * \brief
		 * Write brief comment for RotateView here.
		 * 
		 * \param angle
		 * Description of parameter angle.
		 * 
		 * \param axis
		 * Description of parameter axis.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for RotateView here.
		 * 
		 * \remarks
		 * Write remarks for RotateView here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Camera::RotateView(double angle, Vec3d axis);
		//Purpose:
		//	Rotates the camera by angle degrees about the axis specified by axis.
		
		/*!
		 * \brief
		 * Write brief comment for RotateView here.
		 * 
		 * \param angle
		 * Description of parameter angle.
		 * 
		 * \param X
		 * Description of parameter X.
		 * 
		 * \param Y
		 * Description of parameter Y.
		 * 
		 * \param Z
		 * Description of parameter Z.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for RotateView here.
		 * 
		 * \remarks
		 * Write remarks for RotateView here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void RotateView(double angle, double X, double Y, double Z);
		//Purpose:
		//	Rotates the camera by angle degrees about the axis specified by the given components.
		//		Works the same as glRotatef(angle, X, Y, Z).
	
		/*!
		 * \brief
		 * Write brief comment for SetViewByMouse here.
		 * 
		 * \param window
		 * Description of parameter window.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetViewByMouse here.
		 * 
		 * \remarks
		 * Write remarks for SetViewByMouse here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetViewByMouse(Window window);
		//Purpose:
		//	Updates the view Vector based on the change in mouse position since the last time it was called.
	
		//This function needs to be reimagined and better fleshed out.
		//void RotateAroundPoint(Vec3f vCenter, double X, double Y, double Z);
		//Purpose:
		//	Rotates the camera arount the point vCenter X degrees around the x-axis, Y degrees around the y-axis, and Z degrees around the z-axis in that order
		
		/*!
		 * \brief
		 * Write brief comment for StrafeCamera here.
		 * 
		 * \param speed
		 * Description of parameter speed.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for StrafeCamera here.
		 * 
		 * \remarks
		 * Write remarks for StrafeCamera here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void StrafeCamera(double speed);
		//Purpose:
		//	Moves the camera along it's strafe vector speed units.
		
		/*!
		 * \brief
		 * Write brief comment for MoveCamera here.
		 * 
		 * \param speed
		 * Description of parameter speed.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for MoveCamera here.
		 * 
		 * \remarks
		 * Write remarks for MoveCamera here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void MoveCamera(double speed);
		//Purpose:
		//	Moves the camera along it's view vector speed units.

		/*!
		 * \brief
		 * Write brief comment for Update here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Update here.
		 * 
		 * \remarks
		 * Write remarks for Update here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Update();
		//Purpose:
		//	Recalculates the strafe vector.
	
		/*!
		 * \brief
		 * Write brief comment for Look here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Look here.
		 * 
		 * \remarks
		 * Write remarks for Look here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
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
