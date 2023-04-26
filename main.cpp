#include <iostream>
#include "StabilityTester.h"
#include "Simulation/PerturbationInitializer.h"

int main() {
  SimulationParameters params{.Inertia=Eigen::Matrix3d({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}), // kg km^2
      .Distance=6371};                                                                     // km

  PerturbationInitializer initializer(params, 1e-2, 1e-5);

  StabilityTester tester(params, 1e-2, 1e4, 100, std::make_unique<PerturbationInitializer>(initializer));

  std::cout << tester.TestOrientation();
}
