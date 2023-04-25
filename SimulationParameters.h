//
// Created by Artem Novikov on 21.04.2023.
//

#ifndef GRAVITY__SIMULATIONPARAMETERS_H_
#define GRAVITY__SIMULATIONPARAMETERS_H_

#include <Eigen/Geometry>

struct SimulationParameters {
  SimulationParameters() = delete;

  const Eigen::Matrix<double, 3, 3> Inertia;
  const double Gravity;
  const double distance;
};

#endif //GRAVITY__SIMULATIONPARAMETERS_H_
