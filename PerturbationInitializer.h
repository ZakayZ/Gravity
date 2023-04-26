//
// Created by Artem Novikov on 26.04.2023.
//

#ifndef GRAVITY__PERTURBATIONINITIALIZER_H_
#define GRAVITY__PERTURBATIONINITIALIZER_H_

#include "PositionInitializer.h"
#include "SimulationParameters.h"

class PerturbationInitializer : public PositionInitializer{
 public:
  PerturbationInitializer(const SimulationParameters& parameters, double angle, double angular_velocity);

  Position Initialize() override;

 private:
  double distance_;
  double angle_perturbation_;
  double angular_velocity_perturbation_;
};

#endif //GRAVITY__PERTURBATIONINITIALIZER_H_
