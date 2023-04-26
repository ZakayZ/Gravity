//
// Created by Artem Novikov on 26.04.2023.
//

#include "OrbitalPhysics.h"

const double OrbitalPhysics::GravitationalConstant = 398600.4415; // km^3/c^2

Eigen::Vector3d OrbitalPhysics::Velocity(const Eigen::Vector3d& position, const Eigen::Vector3d& normal) {
  auto distance = position.norm();
  return (std::sqrt(GravitationalConstant / std::pow(distance, 3))) * normal.normalized().cross(position);
}

Eigen::Vector3d OrbitalPhysics::AngularVelocity(const Eigen::Vector3d& position, const Eigen::Vector3d& normal) {
  auto distance = position.norm();
  return normal * (std::sqrt(GravitationalConstant / distance) / distance);
}

double OrbitalPhysics::GetGravity() {
  return GravitationalConstant;
}
