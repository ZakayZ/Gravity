//
// Created by Artem Novikov on 21.04.2023.
//

#ifndef GRAVITY_SATELLITE_SATELLITE_H_
#define GRAVITY_SATELLITE_SATELLITE_H_

#include <functional>
#include "Position.h"
#include "../DataTypes.h"

class Satellite {
 public:
  Satellite(const Eigen::Matrix3d& inertia, double gravity, const Position& initial_position);

  Position& GetPosition() { return position_; }

  const Position& GetPosition() const { return position_; }

  [[nodiscard]] std::function<Position(Time, const Position&)> GetDerivative() const;

 private:
  const Eigen::Matrix3d inertia_;
  const Eigen::Matrix3d inv_inertia_;
  const double gravity_pull_;
  Position position_;
};

#endif //GRAVITY_SATELLITE_SATELLITE_H_
