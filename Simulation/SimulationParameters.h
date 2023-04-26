//
// Created by Artem Novikov on 21.04.2023.
//

#ifndef GRAVITY__SIMULATIONPARAMETERS_H_
#define GRAVITY__SIMULATIONPARAMETERS_H_

#include <Eigen/Geometry>

struct SimulationParameters {
  const Eigen::Matrix<double, 3, 3> Inertia;
  const double Distance;
};

#endif //GRAVITY__SIMULATIONPARAMETERS_H_
