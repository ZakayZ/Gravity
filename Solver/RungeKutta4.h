//
// Created by Artem Novikov on 20.04.2023.
//

#ifndef GRAVITY__RUNGEKUTTA4_H_
#define GRAVITY__RUNGEKUTTA4_H_

#include "Solver.h"

template <typename X, typename Y, class Derivative>
class RungeKutta4 : public Solver<X, Y, Derivative> {
 public:
  void Step(X& x, Y& y, const X& step, Derivative f) override;

  ~RungeKutta4() = default;
};

#endif //GRAVITY__RUNGEKUTTA4_H_
