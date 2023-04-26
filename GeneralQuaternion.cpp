//
// Created by Artem Novikov on 26.04.2023.
//

#include "GeneralQuaternion.h"
GeneralQuaternion::GeneralQuaternion(double w) : scalar(w), vec(0, 0, 0) {}

GeneralQuaternion::GeneralQuaternion(const Eigen::Vector3d& vec) : scalar(0), vec(vec) {}

GeneralQuaternion::GeneralQuaternion(double w, double x, double y, double z) : scalar(w), vec(x, y, z) {}

GeneralQuaternion::GeneralQuaternion(double w, const Eigen::Vector3d& vec) : scalar(w), vec(vec) {}

GeneralQuaternion& GeneralQuaternion::operator*=(const GeneralQuaternion& other) {
  auto s = scalar;
  scalar = other.scalar * s - vec.dot(other.vec);
  vec = s * other.vec + other.scalar * vec + vec.cross(other.vec);
  return *this;
}

GeneralQuaternion& GeneralQuaternion::operator+=(const GeneralQuaternion& other) {
  scalar += other.scalar;
  vec += other.vec;
  return *this;
}

GeneralQuaternion& GeneralQuaternion::operator-=(const GeneralQuaternion& other) {
  scalar -= other.scalar;
  vec -= other.vec;
  return *this;
}

GeneralQuaternion GeneralQuaternion::operator-() const {
  return GeneralQuaternion(-scalar, -vec);
}

GeneralQuaternion GeneralQuaternion::Conjugate() const {
  return GeneralQuaternion(scalar, -vec);
}

Eigen::Vector3d GeneralQuaternion::Transform(const Eigen::Vector3d& vec) const {
  return ((*this) * vec * Conjugate()).vec;
}

//[[nodiscard]] Eigen::Vector3d InverseTransform(const Eigen::Vector3d& vec) const {
//  return (Conjugate() * vec * (*this)).vec;
//}

double GeneralQuaternion::SquaredNorm() const {
  return vec.squaredNorm() + std::pow(scalar, 2);
}

double GeneralQuaternion::Norm() const {
  return std::sqrt(SquaredNorm());
}

GeneralQuaternion operator+(const GeneralQuaternion& lhs, const GeneralQuaternion& rhs) {
  auto result = lhs;
  result += rhs;
  return result;
}

GeneralQuaternion operator-(const GeneralQuaternion& lhs, const GeneralQuaternion& rhs) {
  auto result = lhs;
  result -= rhs;
  return result;
}

GeneralQuaternion operator*(const GeneralQuaternion& lhs, const GeneralQuaternion& rhs) {
  auto result = lhs;
  result *= rhs;
  return result;
}
