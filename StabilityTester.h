//
// Created by Artem Novikov on 22.04.2023.
//

#ifndef GRAVITY__STABILITYTESTER_H_
#define GRAVITY__STABILITYTESTER_H_

#include "SimulationParameters.h"
#include "DataTypes.h"
#include "Satellite/Position.h"
#include "PositionInitializer.h"

class StabilityTester {
 public:
  StabilityTester(const SimulationParameters& parameters,
                  Time step,
                  Time duration,
                  size_t iter_count,
                  std::unique_ptr<PositionInitializer>&& initializer);

  [[nodiscard]] float TestOrientation() const;

 private:
  SimulationParameters parameters_;
  Time step_;
  Time iter_duration_;
  size_t iter_count_;
  std::unique_ptr<PositionInitializer> initializer_;
};

#endif //GRAVITY__STABILITYTESTER_H_
