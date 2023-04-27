//
// Created by Artem Novikov on 26.04.2023.
//

#include "PerturbationInitializer.h"
#include "Random/Randomizer.h"
#include "OrbitalPhysics.h"

PerturbationInitializer::PerturbationInitializer(const SimulationParameters& parameters,
                                                 double angle,
                                                 double angular_velocity)
    : parameters_(parameters),
      angle_perturbation_(angle),
      angular_velocity_perturbation_(angular_velocity) {}

Position PerturbationInitializer::Initialize() const {
  auto position = parameters_.InitialPosition;

  auto velocity = OrbitalPhysics::Velocity(position, parameters_.Normal);

  auto axis = Randomizer::IsotropicVector();
  auto angle = Randomizer::NormalDistribution(0, angle_perturbation_);
  auto orientation = GeneralQuaternion(std::cos(angle / 2), axis * std::sin(angle / 2));

  auto outer_rotation = OrbitalPhysics::AngularVelocity(position, parameters_.Normal);
  Eigen::Vector3d delta_velocity =
      Randomizer::IsotropicVector() * Randomizer::NormalDistribution(0, angular_velocity_perturbation_);
  auto angular_velocity = orientation.InverseTransform(outer_rotation + delta_velocity);

  return {position, velocity, orientation, angular_velocity};
}
