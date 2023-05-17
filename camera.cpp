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

// clang-format off
#include "camera.h"
#include "opengl.h"

// clang-format on

namespace OpenArena {

Camera::Camera() : _position(0, 0, 0), _heading(0, 0, 0), _up(0, 1, 0) {}

void Camera::PositionCamera(double xpos, double ypos, double zpos, double xview, double yview, double zview, double xup,
                            double yup, double zup) {
  _position = Vec3f(xpos, ypos, zpos);
  _heading = Vec3f(xview - xpos, yview - ypos, zview - zpos);
  _up = Vec3f(xup, yup, zup).normalized();
  UpdateVectors();
}

void Camera::PositionCamera(Vec3f pos, Vec3f view, Vec3f up) {
  _position = pos;
  _heading = view - pos;
  _up = up;
  UpdateVectors();
}

void Camera::SetViewByMouse(Window window) {
  static double currentRotX = 0.0f;
  Vec2i pos;
  Vec2i middle;
  double angleZ;

  middle.x = window.GetWidth() / 2;
  middle.y = window.GetHeight() / 2;
  pos = window.GetMousePosition();
  if (pos != middle) {
    window.SetMousePosition(middle);
    angleZ = (middle.y - pos.y) / 1000.0;
    currentRotX -= angleZ;
    if (currentRotX > 1.0) {
      currentRotX = 1.0;
    } else if (currentRotX < -1.0) {
      currentRotX = -1.0;
    } else {
      Vec3d axis = (_heading).cross(_up);
      axis.normalize();
      RotateView(angleZ, axis.x, axis.y, axis.z);
      RotateView((middle.x - pos.x) / 1000.0, 0, 1, 0);
      // RotateView((middle.x-pos.x)/1000.0, m_vUpVector.x, m_vUpVector.y,
      // m_vUpVector.z);
    }
  }
}

void Camera::MoveCamera(double speed) {
  _position = _position + _heading * speed;
  UpdateVectors();
}

void Camera::RotateView(double angle, Vec3d axis) {
  // Maybe make this not call the other RotateView later
  axis.normalize();
  RotateView(angle, axis.x, axis.y, axis.z);
}

void Camera::RotateView(double angle, double x, double y, double z) {
  double cosTheta = cos(angle);
  double sinTheta = sin(angle);

  double newX = (cosTheta + (1 - cosTheta) * x * x) * _heading.x + ((1 - cosTheta) * x * y - z * sinTheta) * _heading.y
              + ((1 - cosTheta) * x * z + y * sinTheta) * _heading.z;

  double newY = (cosTheta + (1 - cosTheta) * y * y) * _heading.y + ((1 - cosTheta) * x * y + z * sinTheta) * _heading.x
              + ((1 - cosTheta) * y * z - x * sinTheta) * _heading.z;

  double newZ = (cosTheta + (1 - cosTheta) * z * z) * _heading.z + ((1 - cosTheta) * x * z - y * sinTheta) * _heading.x
              + ((1 - cosTheta) * y * z + x * sinTheta) * _heading.y;

  _heading.x = newX;
  _heading.y = newY;
  _heading.z = newZ;
}

void Camera::StrafeCamera(double speed) {
  _position = _position + _strafe * speed;
}

void Camera::Update() {
  _strafe = ((_heading).cross(_up)).normalized();
}

void Camera::Look() {
  Vec3f view = _position + _heading;
  gluLookAt(_position.x, _position.y, _position.z, view.x, view.y, view.z, _up.x, _up.y, _up.z);
}

Vec3f Camera::Position() {
  return _position;
}

Vec3f Camera::Strafe() {
  return _strafe;
}

Vec3f Camera::UpVector() {
  return _up;
}

Vec3f Camera::View() {
  return _heading + _position;
}

void Camera::RotateHorizontal(float angle) {
  RotateView(angle, GetUpVector());
}

void Camera::RotateVertical(float angle) {
  RotateView(angle, GetRightVector());
}

Vec3f Camera::GetUpVector() {
  return _up;
}

Vec3f Camera::GetRightVector() {
  return _strafe;
}

Vec3f Camera::GetForwardVector() {
  return _heading;
}

void Camera::UpdateVectors() {}

};  // End namespace OpenArena
