//
// Created by Artem Novikov on 22.04.2023.
//

#ifndef GRAVITY__SIMULATION_H_
#define GRAVITY__SIMULATION_H_

#include <memory>
#include <functional>

#include "DataTypes.h"
#include "Satellite/Satellite.h"
#include "Solver/Solver.h"
#include "Metrics/Metric.h"

class Simulation {
 public:
  using SimulationSolver = Solver<Time, Position, std::function<Position(Time, const Position&)>>;

  Simulation(const Satellite& satellite, Time step, std::unique_ptr<SimulationSolver>&& solver, Metric<Time, Position>& metrics_monitor);

  void Run(Time duration);

  [[nodiscard]] const Satellite& GetSatellite() const { return satellite_; }

 private:
  Satellite satellite_;
  Time step_;
  Time elapsed_time_;
  std::unique_ptr<SimulationSolver> solver_;
  Metric<Time, Position>& monitor_;
};

#endif //GRAVITY__SIMULATION_H_
