//
// Created by Artem Novikov on 20.04.2023.
//

#ifndef GRAVITY__RUNGEKUTTA4_H_
#define GRAVITY__RUNGEKUTTA4_H_

#include "Solver.h"

template <typename X, typename Y, class Derivative>
class RungeKutta4 : public Solver<X, Y, Derivative> {
 public:
  void Step(X& x, Y& y, const X& step, Derivative f) override {
    auto k1 = f(x, y) * step;
    auto k2 = f(x + step * 0.5, y + k1 * 0.5) * step;
    auto k3 = f(x + step * 0.5, y + k2 * 0.5) * step;
    auto k4 = f(x + step, y + k3) * step;
    x += step;
    y += (k1 + 2. * k2 + 2. * k3 + k4) / 6.;
    y.Fix();
  }

  ~RungeKutta4() = default;
};

#endif //GRAVITY__RUNGEKUTTA4_H_
