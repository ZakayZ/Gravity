//
// Created by Artem Novikov on 22.04.2023.
//

#include <boost/asio.hpp>

#include "StabilityTester.h"
#include "Simulation/Simulation.h"
#include "Solver/RungeKutta4.h"
#include "Metrics/StabilityMetric.h"
#include "OrbitalPhysics.h"

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
  const double threshold = 0.05;

  std::atomic<size_t> stable_iters = 0;

  ThreadPool pool(10);

  for (size_t i = 0; i < iter_count_; ++i) {
    auto func = [&]() {
      auto orbital_angular_velocity = OrbitalPhysics::AngularVelocity(parameters_.InitialPosition,
                                                                      parameters_.Normal);
      StabilityMetric monitor(orbital_angular_velocity, threshold, threshold);

      Simulation simulation(Satellite(parameters_.Inertia, initializer_->Initialize()),
                            step_,
                            std::make_unique<TesterSolver>(),
                            monitor);

      simulation.Run(iter_duration_);

      if (monitor.IsStable()) {
        stable_iters.fetch_add(1);
      }
    };
//    func();
    boost::asio::post(pool, func);
  }

  pool.join();

  return float(stable_iters) / float(iter_count_);
}
