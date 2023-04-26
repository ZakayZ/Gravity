//
// Created by Artem Novikov on 21.04.2023.
//

#include "Position.h"

Position::Position(const Eigen::Vector3d& initial_position,
                   const Eigen::Vector3d& initial_velocity,
                   const GeneralQuaternion& initial_orientation,
                   const Eigen::Vector3d& initial_angular_velocity)
    : position_(initial_position),
      velocity_(initial_velocity),
      orientation_(initial_orientation),
      angular_velocity_(initial_angular_velocity) {}

Position& Position::operator+=(const Position& other) {
  position_ += other.position_;

  velocity_ += other.velocity_;

  orientation_.x() += other.orientation_.x();
  orientation_.y() += other.orientation_.y();
  orientation_.z() += other.orientation_.z();
  orientation_.w() += other.orientation_.w();

  angular_velocity_ += other.angular_velocity_;

  return *this;
}

Position& Position::operator-=(const Position& other) {
  position_ -= other.position_;

  velocity_ -= other.velocity_;

  orientation_.x() -= other.orientation_.x();
  orientation_.y() -= other.orientation_.y();
  orientation_.z() -= other.orientation_.z();
  orientation_.w() -= other.orientation_.w();

  angular_velocity_ -= other.angular_velocity_;

  return *this;
}

Position& Position::operator*=(double scalar) {
  position_ *= scalar;

  velocity_ *= scalar;

  orientation_.x() *= scalar;
  orientation_.y() *= scalar;
  orientation_.z() *= scalar;
  orientation_.w() *= scalar;

  angular_velocity_ *= scalar;

  return *this;
}

Position& Position::operator/=(double scalar) {
  position_ /= scalar;

  velocity_ /= scalar;

  orientation_.x() /= scalar;
  orientation_.y() /= scalar;
  orientation_.z() /= scalar;
  orientation_.w() /= scalar;

  angular_velocity_ /= scalar;

  return *this;
}

void Position::NormaliseOrientation() {
  auto norm = orientation_.Norm();

  orientation_.x() /= norm;
  orientation_.y() /= norm;
  orientation_.z() /= norm;
  orientation_.w() /= norm;
}

void Position::Fix() {
  NormaliseOrientation();
}

Position operator+(const Position& lhs, const Position& rhs) {
  auto copy = lhs;
  copy += rhs;
  return copy;
}

Position operator-(const Position& lhs, const Position& rhs) {
  auto copy = lhs;
  copy -= rhs;
  return copy;
}

Position operator*(const Position& pos, double scalar) {
  auto copy = pos;
  copy *= scalar;
  return copy;
}

Position operator*(double scalar, const Position& pos) {
  return pos * scalar;
}

Position operator/(const Position& pos, double scalar) {
  auto copy = pos;
  copy /= scalar;
  return copy;
}