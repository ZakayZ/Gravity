//
// Created by Artem Novikov on 19.02.2023.
//

#include <random>
#include <numbers>

#include "Randomizer.h"

double Randomizer::UniformRealDistribution() {
  static std::random_device device;
  static std::mt19937 generator(device());
  static std::uniform_real_distribution<double> distribution(0, 1);
  return distribution(generator);
}

double Randomizer::NormalDistribution(double mean, double deviation) {
  static std::random_device device;
  static std::mt19937 generator(device());
  static std::normal_distribution<double> distribution(0, 1);
  return mean + distribution(generator) * deviation;
}

Eigen::Vector3d Randomizer::IsotropicVector(double magnitude) {
  auto cos = 1.0 - 2.0 * UniformRealDistribution();
  auto sin = std::sqrt(1.0 - std::pow(cos, 2));
  auto phi = std::numbers::pi * UniformRealDistribution();
  Eigen::Vector3d momentum(magnitude * std::cos(phi) * sin,
                            magnitude * std::sin(phi) * sin,
                            magnitude * cos);
//  Eigen::Vector3d momentum(NormalDistribution(), NormalDistribution(), NormalDistribution());
//  momentum = momentum * (magnitude) / momentum.mag();
  return momentum;
}