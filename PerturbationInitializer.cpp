//
// Created by Artem Novikov on 26.04.2023.
//

#include "PerturbationInitializer.h"
#include "Random/Randomizer.h"
#include "OrbitalPhysics.h"

PerturbationInitializer::PerturbationInitializer(const SimulationParameters& parameters,
                                                 double angle,
                                                 double angular_velocity)
    : distance_(parameters.Distance),
      angle_perturbation_(angle),
      angular_velocity_perturbation_(angular_velocity) {}

Position PerturbationInitializer::Initialize() {
  auto motion_normal = Eigen::Vector3d(0, 0, 1);

  auto position = Eigen::Vector3d(distance_, 0, 0);

  auto velocity = OrbitalPhysics::Velocity(position, motion_normal);

  auto axis = Randomizer::IsotropicVector();
  auto angle = Randomizer::NormalDistribution(0, angle_perturbation_);
  auto sin = std::sin(angle / 2);
  auto orientation = Eigen::Quaterniond(std::cos(angle / 2), axis.x() * sin, axis.y() * sin, axis.z() * sin);

  auto outer_rotation = OrbitalPhysics::AngularVelocity(position, motion_normal);
  auto angular_velocity = orientation._transformVector(
      outer_rotation
          + Randomizer::IsotropicVector() * Randomizer::NormalDistribution(angular_velocity_perturbation_));
  return {position, velocity, orientation, angular_velocity};
}
