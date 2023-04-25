//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_RANDOMIZER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_RANDOMIZER_H_

#include <vector>
#include <Eigen/Geometry>

class Randomizer {
 public:
  static double UniformRealDistribution();

  static double NormalDistribution(double mean = 0, double deviation = 1);

  static Eigen::Vector3d IsotropicVector(double magnitude = 1);
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_RANDOMIZER_H_
