//
// Created by Artem Novikov on 21.04.2023.
//

#include "Satellite.h"
#include "cmath"

Satellite::Satellite(const Eigen::Matrix3d& inertia, double gravity, const Position& initial_position)
    : inertia_(inertia),
      inv_inertia_(inertia.inverse()),
      gravity_pull_(gravity),
      position_(initial_position) {}

std::function<Position(Time, const Position&)> Satellite::GetDerivative() const {
  return [&inertia = inertia_, &inv_inertia = inv_inertia_, grav = gravity_pull_]
      (Time, const Position& pos) -> Position {
    auto ang_velocity_quaternion = Eigen::Quaterniond(0,
                                                      pos.GetAngVelocity().x(),
                                                      pos.GetAngVelocity().y(),
                                                      pos.GetAngVelocity().z());
    auto distance = pos.GetPosition().norm();
    auto norm_direction = pos.GetPosition() / distance;
    auto norm_direction_e = pos.GetOrientation()._transformVector(norm_direction);
    auto gravity_momentum = (-3 * grav / std::pow(distance, 3)) * norm_direction_e.cross(inertia * norm_direction_e);
    return {pos.GetVelocity(),
            (-grav / std::pow(distance, 2)) * norm_direction,
            0.5 * (pos.GetOrientation() * ang_velocity_quaternion),
            inv_inertia * (pos.GetAngVelocity().cross(inertia * pos.GetAngVelocity()) + gravity_momentum)};
  };
}
