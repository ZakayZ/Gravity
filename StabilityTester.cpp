//
// Created by Artem Novikov on 22.04.2023.
//

#include <boost/asio.hpp>

#include "StabilityTester.h"
#include "Simulation/Simulation.h"
#include "Metrics/Metric.h"
#include "Solver/RungeKutta4.h"

using ThreadPool = boost::asio::thread_pool;

using TesterSolver = RungeKutta4<Time, Position,
                                 std::function<Position(Time, const Position&)>>;

StabilityTester::StabilityTester(const SimulationParameters& parameters,
                                 Time step,
                                 Time duration,
                                 size_t iter_count,
                                 std::unique_ptr<PositionInitializer>&& initializer)
    : parameters_(parameters),
      step_(step),
      iter_duration_(duration),
      iter_count_(iter_count),
      initializer_(std::move(initializer)) {}

float StabilityTester::TestOrientation() const {
  Metric<Time, Position> empty_metric;

  double threshold = 0.01;

  std::atomic<size_t> stable_iters = 0;

  ThreadPool pool(10);

  for (size_t i = 0; i < iter_count_; ++i) {
    auto func = [&]() {
      Metric<Time, Position> monitor;
      Simulation simulation(Satellite(parameters_.Inertia, initializer_->Initialize()),
                            step_,
                            std::make_unique<TesterSolver>(),
                            monitor);
      auto initial_angular_velocity = simulation.GetSatellite().GetPosition().GetAbsAngVelocity();
      auto initial_distance = simulation.GetSatellite().GetPosition().GetAngVelocity().norm();
      simulation.Run(iter_duration_);

      assert(std::abs(initial_distance - simulation.GetSatellite().GetPosition().GetAngVelocity().norm())
                 < 0.01); // sanity check

      if ((simulation.GetSatellite().GetPosition().GetAbsAngVelocity() - initial_angular_velocity).norm()
          <= threshold * initial_angular_velocity.norm()) {
        stable_iters.fetch_add(1);
      }
    };
    boost::asio::post(pool, func);
  }

  pool.join();

  return float(stable_iters) / float(iter_count_);
}
