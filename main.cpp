#include <array>
#include "StabilityTester.h"
#include "Simulation/PerturbationInitializer.h"

int main() {
  std::array<double, 3> inertia = {2, 3, 4};
  double sigma_phi = 1e-3, sigma_w = 1e-5;

  double distance = 6371;
  double simulation_time = 1e4;
  double simulation_step = 1e-2;
  size_t iterations = 100;

  std::array<size_t, 3> permutation = {0, 1, 2};
  std::string names = "ABC";

  do {
    SimulationParameters params
        {.Inertia=Eigen::Matrix3d({{inertia[permutation[0]], 0, 0},
                                   {0, inertia[permutation[1]], 0},
                                   {0, 0, inertia[permutation[2]]}}), // kg km^2
            .InitialPosition=Eigen::Vector3d(distance, 0, 0),
            .Normal=Eigen::Vector3d(0, 0, 1)};                                      // km

    StabilityTester tester(params, simulation_step, simulation_time, iterations,
                           std::make_unique<PerturbationInitializer>(params, sigma_phi, sigma_w));

    std::printf("The orientation %c, %c, %c was stable in %.1f %% of runs\n",
                names[permutation[0]],
                names[permutation[1]],
                names[permutation[2]],
                tester.TestOrientation() * 100);
  } while (std::next_permutation(permutation.begin(), permutation.end()));
}
