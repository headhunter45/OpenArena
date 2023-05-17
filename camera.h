/***************************************************************************
 *   Copyright (C) 2001-2023 by Tom Hicks                                  *
 *   headhunter3@gmail.com                                                 *
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

#ifndef OpenArena__camera_h__
#define OpenArena__camera_h__

// clang-format off
#include "config.h"
#include <cmath>
#include "window.h"

// clang-format on

namespace OpenArena {
/// @brief The Camera class represents a camera or view in 3-dimensional space.
///
/// The Camera class maintains location, view, and orientation (up view) vectors.
/// The Camera can be moved and rotated in any direction.  It includes a wrapper,
/// Look(), for gluLookAt.
class Camera {
 public:
  /// @brief Creates a new Camera object.
  /// Creates a new Camera object located at the origin, pointing at the negative
  /// z-axis with up being the positive y-axis.
  Camera();

  // Camera(const Camera&);	//Copy Constructor

  /// @brief Returns this Camera's position.
  /// @return This Camera's position as a Vec3d vector
  Vec3f Position();

  /// @brief Returns the view vector of this camera.
  /// @return The view vector of this camera.
  Vec3d View();

  /// @brief Returns a vector pointing up with respect to the view.
  /// @return A vector pointing up with respect to the view.
  Vec3d UpVector();

  /// @brief Returns this Camera's strafe vector.
  /// The strafe axis is an axis perpendicular to both the up vector and the view vector.
  /// @return This Camera's strafe vector.
  Vec3d Strafe();

  /// @brief Relocates and reorients this Camera.
  /// @param xpos The x-cooridnate of the new position vector.
  /// @param ypos The y-coordinate of the new position vector.
  /// @param zpos The z-coordinate of the new position vector.
  /// @param xview The x-coordinate of the new view vector.
  /// @param yview The y-coordiante of the new view vector.
  /// @param zview The z-cooridnate of the new view vector.
  /// @param xup The x-coordinate of the new up vector.
  /// @param yup The y-coordinate of the new up vector.
  /// @param zup The z-coordinate of the new up vector.
  void PositionCamera(double xpos, double ypos, double zpos, double xview, double yview, double zview, double xup,
                      double yup, double zup);

  /// @brief Relocates and reorients this Camera.
  /// @param pos The new position vector.
  /// @param view The new view vector.
  /// @param up The new up vector.
  void PositionCamera(Vec3d pos, Vec3d view, Vec3d up);

  /// @brief Rotates the camera a given amount around a given axis.
  /// @param angle The number of degrees to rotate. Is this actually degrees not radians?
  /// @param axis A vector representing the axis to rotate around.
  /// This method passes the arguments to glRotatef().
  void RotateView(double angle, Vec3d axis);

  /// @brief Rotates the camera a given amount around a given axis.
  /// @param angle The number of degrees to rotate.
  /// @param X The x-component of the vector representing the axis to rotate around.
  /// @param Y The y-component of the vector representing the axis to rotate around.
  /// @param Z The z-component of the vector representing the axis to rotate around.
  /// The vector should be normalized as the values get passed directly to glRotatef().
  void RotateView(double angle, double X, double Y, double Z);

  /// @brief Updates the view and up vectors based on mouse movement.
  /// @param window The Window used to get the mouse coordinates.
  /// This will be removed in favor of some sort of event trigger.
  void SetViewByMouse(Window window);

  /// @brief Moves the camera along its strafe axis a given distance.
  /// @param speed The distance to move.
  void StrafeCamera(double speed);

  // Purpose:
  //	Moves the camera along it's strafe vector speed units.

  /// @brief Moves the camera along its view vector a given number of units.
  /// @param speed The distance to move the camera.
  void MoveCamera(double speed);

  /// @brief Recalculates the strafe vector.
  void Update();

  /// @brief Calls gluLookAt to tell OpenGL where to render from.
  /// Uses the position, view, and up vectors.
  void Look();

  void RotateHorizontal(float angle);

  void RotateVertical(float angle);

 private:
  Vec3f GetUpVector();

  /// @brief Returns a unit vector pointing to the immediate right of the current view.
  /// @return A unit vector pointing to the immediate right of the current view.
  /// Returns a unit vector pointing to the immediate right of the current view. This is the direction of a positive
  /// strafe movement.
  Vec3f GetRightVector();

  /// @brief Returns a unit vector pointing directly into the current view.
  /// @return A unit vector pointing directly into the current view.
  /// Returns a unit vector pointing directly into the current view. This is the direction of positive movement.
  Vec3f GetForwardVector();

  void UpdateVectors();

 private:
  Vec3f _heading;
  Vec3f _position;
  Vec3f _up;
  Vec3f _strafe;
};
}  // End namespace OpenArena

#endif  // End !defined(OpenArena__camera_h__)
