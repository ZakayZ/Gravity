//
// Created by Artem Novikov on 21.04.2023.
//

#ifndef GRAVITY__POSITION_H_
#define GRAVITY__POSITION_H_

#include <Eigen/Geometry>

class Position {
 public:
  Position(const Eigen::Vector3d& initial_position,
           const Eigen::Vector3d& initial_velocity,
           const Eigen::Quaternion<double>& initial_orientation,
           const Eigen::Vector3d& initial_angular_velocity);

  Position(const Position& other) = default;

  Position(Position&& other) = default;

  Position& operator=(const Position& other) = default;

  Position& operator=(Position&& other) = default;

  Position& operator+=(const Position& other);

  Position& operator-=(const Position& other);

  Position& operator*=(double scalar);

  Position& operator/=(double scalar);

  Eigen::Vector3d& GetPosition() { return position_; }

  [[nodiscard]] const Eigen::Vector3d& GetPosition() const { return position_; }

  Eigen::Vector3d& GetVelocity() { return velocity_; }

  [[nodiscard]] const Eigen::Vector3d& GetVelocity() const { return velocity_; }

  Eigen::Quaterniond& GetOrientation() { return orientation_; }

  [[nodiscard]] const Eigen::Quaterniond& GetOrientation() const { return orientation_; }

  Eigen::Vector3d& GetAngVelocity() { return angular_velocity_; }

  [[nodiscard]] const Eigen::Vector3d& GetAngVelocity() const { return angular_velocity_; }

  [[nodiscard]] Eigen::Vector3d GetAbsAngVelocity() const { return orientation_._transformVector(angular_velocity_); }

 private:
  void NormaliseOrientation();

  Eigen::Vector3d position_;
  Eigen::Vector3d velocity_;
  Eigen::Quaterniond orientation_;
  Eigen::Vector3d angular_velocity_;
};

Eigen::Quaterniond operator*(const Eigen::Quaterniond& q, double scale);

Eigen::Quaterniond operator/(const Eigen::Quaterniond& q, double scale);

Eigen::Quaterniond operator*(double scale, const Eigen::Quaterniond& q);

Position operator+(const Position& lhs, const Position& rhs);

Position operator-(const Position& lhs, const Position& rhs);

Position operator*(const Position& pos, double scalar);

Position operator*(double scalar, const Position& pos);

Position operator/(const Position& pos, double scalar);

#endif //GRAVITY__POSITION_H_
