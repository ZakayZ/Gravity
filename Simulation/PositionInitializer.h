//
// Created by Artem Novikov on 26.04.2023.
//

#ifndef GRAVITY__POSITIONINITIALIZER_H_
#define GRAVITY__POSITIONINITIALIZER_H_

#include "Satellite/Position.h"

class PositionInitializer {
 public:
  virtual Position Initialize() const = 0;

  virtual ~PositionInitializer() = default;
};

#endif //GRAVITY__POSITIONINITIALIZER_H_
