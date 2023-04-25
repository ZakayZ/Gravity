//
// Created by Artem Novikov on 20.04.2023.
//

#ifndef GRAVITY__SOLVER_H_
#define GRAVITY__SOLVER_H_

template <typename X, typename Y, class Derivative>
class Solver {
 public:
  virtual void Step(X& x, Y& y, const X& step, Derivative f) = 0;

  virtual ~Solver() = default;
};

#endif //GRAVITY__SOLVER_H_
