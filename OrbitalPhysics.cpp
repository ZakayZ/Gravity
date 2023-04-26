//
// Created by Artem Novikov on 26.04.2023.
//

#include "OrbitalPhysics.h"

const double OrbitalPhysics::GravitationalConstant = 1;

Eigen::Vector3d OrbitalPhysics::Velocity(Eigen::Vector3d position, Eigen::Vector3d normal) {
  return (std::sqrt(GravitationalConstant / position.squaredNorm())) * normal.normalized().cross(position);
}

Eigen::Vector3d OrbitalPhysics::AngularVelocity(Eigen::Vector3d position, Eigen::Vector3d normal) {
  auto distance = position.norm();
  return normal * (std::sqrt(GravitationalConstant / distance) / distance);
}

double OrbitalPhysics::GetGravity() {
  return GravitationalConstant;
}
