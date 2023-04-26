//
// Created by Artem Novikov on 21.04.2023.
//

#include "Satellite.h"
#include "cmath"
#include "../OrbitalPhysics.h"

Satellite::Satellite(const Eigen::Matrix3d& inertia, const Position& initial_position)
    : inertia_(inertia), inv_inertia_(inertia.inverse()), position_(initial_position) {}

std::function<Position(Time, const Position&)> Satellite::GetDerivative() const {
  return [&inertia = inertia_, &inv_inertia = inv_inertia_, grav = OrbitalPhysics::GetGravity()]
      (Time, const Position& pos) -> Position {
    auto ang_velocity_quaternion = Eigen::Quaterniond(0,
                                                      pos.GetAngVelocity().x(),
                                                      pos.GetAngVelocity().y(),
                                                      pos.GetAngVelocity().z());
    auto distance = pos.GetPosition().norm();
    Eigen::Vector3d norm_direction = pos.GetPosition() / distance;
    Eigen::Vector3d norm_direction_e = pos.GetOrientation().conjugate()._transformVector(norm_direction);
    Eigen::Vector3d gravity_momentum = (3 * grav / std::pow(distance, 3)) * norm_direction_e.cross(inertia * norm_direction_e);
    return {pos.GetVelocity(),
            (-grav / std::pow(distance, 2)) * norm_direction,
            0.5 * (pos.GetOrientation() * ang_velocity_quaternion),
            -inv_inertia * (pos.GetAngVelocity().cross(inertia * pos.GetAngVelocity()) + gravity_momentum)};
  };
}
