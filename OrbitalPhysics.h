//
// Created by Artem Novikov on 26.04.2023.
//

#ifndef GRAVITY__ORBITALPHYSICS_H_
#define GRAVITY__ORBITALPHYSICS_H_

#include <Eigen//Geometry>

class OrbitalPhysics {
 public:
  static Eigen::Vector3d Velocity(Eigen::Vector3d position, Eigen::Vector3d normal);

  static Eigen::Vector3d AngularVelocity(Eigen::Vector3d position, Eigen::Vector3d normal);

  static double GetGravity();

 private:
  static const double GravitationalConstant;
};

#endif //GRAVITY__ORBITALPHYSICS_H_
