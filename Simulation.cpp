//
// Created by Artem Novikov on 22.04.2023.
//

#include "Simulation.h"

Simulation::Simulation(const Satellite& satellite,
                       Time step,
                       std::unique_ptr<SimulationSolver>&& solver,
                       Metric<Time, Position>& metrics_monitor)
    : satellite_(satellite), step_(step), elapsed_time_(0), solver_(std::move(solver)), monitor_(metrics_monitor) {}

void Simulation::Run(Time duration) {
  Time current_time = 0;
  while (current_time < duration) {
    monitor_.AddDataPoint(current_time, satellite_.GetPosition());
    solver_->Step(current_time, satellite_.GetPosition(), step_, satellite_.GetDerivative());
  }

  monitor_.AddDataPoint(current_time, satellite_.GetPosition());
}
