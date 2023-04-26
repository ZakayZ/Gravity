//
// Created by Artem Novikov on 26.04.2023.
//

#ifndef GRAVITY_METRICS_STABILITYMETRIC_H_
#define GRAVITY_METRICS_STABILITYMETRIC_H_

#include "Metric.h"
#include "DataTypes.h"
#include "Satellite/Position.h"

class StabilityMetric : public Metric<Time, Position> {
 public:
  StabilityMetric(const Eigen::Vector3d& angular_velocity,
                  double ang_velocity_prox,
                  double orientation_prox);

  void AddDataPoint(const Time& time, const Position& pos) override;

  [[nodiscard]] bool IsStable() const { return is_stable_; }

 private:
  Eigen::Vector3d target_angular_velocity_;

  double angular_velocity_proximity_;
  double orientation_proximity_;

  bool is_stable_;
};

#endif //GRAVITY_METRICS_STABILITYMETRIC_H_
