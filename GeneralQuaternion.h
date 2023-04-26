//
// Created by Artem Novikov on 26.04.2023.
//

#ifndef GRAVITY__GENERALQUATERNION_H_
#define GRAVITY__GENERALQUATERNION_H_

#include "Eigen/Geometry"

class GeneralQuaternion {
 public:
  GeneralQuaternion(double w);

  GeneralQuaternion(const Eigen::Vector3d& vec);

  GeneralQuaternion(double w, double x, double y, double z);

  GeneralQuaternion(double w, const Eigen::Vector3d& vec);

  GeneralQuaternion(const GeneralQuaternion&) = default;

  GeneralQuaternion(GeneralQuaternion&&) = default;

  GeneralQuaternion& operator=(const GeneralQuaternion&) = default;

  GeneralQuaternion& operator=(GeneralQuaternion&&) = default;

  GeneralQuaternion& operator*=(const GeneralQuaternion& other);

  GeneralQuaternion& operator+=(const GeneralQuaternion& other);

  GeneralQuaternion& operator-=(const GeneralQuaternion& other);

  GeneralQuaternion operator-() const;

  [[nodiscard]] GeneralQuaternion Conjugate() const;

  [[nodiscard]] Eigen::Vector3d Transform(const Eigen::Vector3d& vec) const;

  [[nodiscard]] Eigen::Vector3d InverseTransform(const Eigen::Vector3d& vec) const;

  [[nodiscard]] double SquaredNorm() const;

  [[nodiscard]] double Norm() const;

  double& x() { return vec.x(); };

  [[nodiscard]] double x() const { return vec.x(); };

  double& y() { return vec.y(); };

  [[nodiscard]] double y() const { return vec.y(); };

  double& z() { return vec.z(); };

  [[nodiscard]] double z() const { return vec.z(); };

  double& w() { return scalar; };

  [[nodiscard]] double w() const { return scalar; };

  Eigen::Vector3d vec;
  double scalar;
};

GeneralQuaternion operator+(const GeneralQuaternion& lhs, const GeneralQuaternion& rhs);

GeneralQuaternion operator-(const GeneralQuaternion& lhs, const GeneralQuaternion& rhs);

GeneralQuaternion operator*(const GeneralQuaternion& lhs, const GeneralQuaternion& rhs);

#endif //GRAVITY__GENERALQUATERNION_H_
