//
// Created by Artem Novikov on 26.04.2023.
//

#ifndef GRAVITY_METRICS_METRIC_H_
#define GRAVITY_METRICS_METRIC_H_

template <typename X, typename Y>
class Metric {
 public:
  virtual void AddDataPoint(const X&, const Y&) {}

  virtual ~Metric() = default;
};

#endif //GRAVITY_METRICS_METRIC_H_
