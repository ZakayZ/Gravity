//
// Created by Artem Novikov on 26.04.2023.
//

#include "StabilityMetric.h"

StabilityMetric::StabilityMetric(const Eigen::Vector3d& angular_velocity,
                                 double ang_velocity_prox,
                                 double orientation_prox)
    : target_angular_velocity_(angular_velocity),
      angular_velocity_proximity_(ang_velocity_prox),
      orientation_proximity_(orientation_prox),
      is_stable_(true) {}

void StabilityMetric::AddDataPoint(const Time& time, const Position& pos) {
  auto ang_velocity_module = target_angular_velocity_.norm();

  if ((pos.GetAbsAngVelocity() - target_angular_velocity_).norm()
      >= angular_velocity_proximity_ * ang_velocity_module) {
    is_stable_ = false;
  }

  auto angle = 0.5 * time * ang_velocity_module;
  auto target_orientation = GeneralQuaternion(std::cos(angle), std::sin(angle) * target_angular_velocity_.normalized());

  assert(std::abs(1 - target_orientation.Norm()) < 0.01);
  assert(std::abs(1 - pos.GetOrientation().Norm()) < 0.01);

  if ((pos.GetOrientation() - target_orientation).Norm() >= orientation_proximity_) {
    is_stable_ = false;
  }
}

