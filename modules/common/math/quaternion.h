/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 * @brief Contains a number of helper functions related to quaternions.
 * The reader should refer to euler_angles_zxy.h for clarifications.
 * However, although the vehicle frame defined therein might change,
 * the definition of the heading of the car, used below, is permanently fixed:
 * 0 at East, pi/2 at North, -pi/2 at South.
 */

#pragma once

#include <cmath>

#include "Eigen/Dense"
#include "Eigen/Geometry"

#include "modules/common_msgs/basic_msgs/geometry.pb.h"

#include "modules/common/math/euler_angles_zxy.h"
#include "modules/common/math/math_utils.h"

/**
 * @namespace apollo::common::math
 * @brief apollo::common::math
 */
namespace apollo {
namespace common {
namespace math {

/*
 * @brief Returns heading (in radians) in [-PI, PI), with 0 being East.
 * Note that x/y/z is East/North/Up.
 *
 * @param qw Quaternion w-coordinate
 * @param qx Quaternion x-coordinate
 * @param qy Quaternion y-coordinate
 * @param qz Quaternion z-coordinate
 *
 * @return Heading encoded by given quaternion
 */
inline double QuaternionToHeading(const double qw, const double qx,
                                  const double qy, const double qz) {
  EulerAnglesZXYd euler_angles(qw, qx, qy, qz);
  // euler_angles.yaw() is zero when the car is pointing North, but
  // the heading is zero when the car is pointing East.
  return NormalizeAngle(euler_angles.yaw() + M_PI_2);
}

/*
 * @brief Returns heading (in radians) in [-PI, PI), with 0 being East.
 * Note that x/y/z is East/North/Up.
 *
 * @param q Eigen::Quaternion
 *
 * @return Heading encoded by given quaternion
 */
template <typename T>
inline T QuaternionToHeading(const Eigen::Quaternion<T> &q) {
  return static_cast<T>(QuaternionToHeading(q.w(), q.x(), q.y(), q.z()));
}

/*
 * @brief Returns a quaternion encoding a rotation with zero roll, zero pitch,
 * and the specified heading/yaw.
 * Note that heading is zero at East and yaw is zero at North.
 * Satisfies QuaternionToHeading(HeadingToQuaternion(h)) = h.
 *
 * @param heading The heading to encode in the rotation
 *
 * @return Quaternion encoding rotation by given heading
 */
template <typename T>
inline Eigen::Quaternion<T> HeadingToQuaternion(T heading) {
  // Note that heading is zero at East and yaw is zero at North.
  EulerAnglesZXY<T> euler_angles(heading - M_PI_2);
  return euler_angles.ToQuaternion();
}

/*
 * @brief Applies the rotation defined by a quaternion to a given vector.
 * Note that x/y/z is East/North/Up.
 *
 * @param orientation Quaternion
 * @param original Vector (in East-North-Up frame)
 *
 * @return Rotated vector
 */
inline Eigen::Vector3d QuaternionRotate(const Quaternion &orientation,
                                        const Eigen::Vector3d &original) {
  Eigen::Quaternion<double> quaternion(orientation.qw(), orientation.qx(),
                                       orientation.qy(), orientation.qz());
  return static_cast<Eigen::Vector3d>(quaternion.toRotationMatrix() * original);
}

inline Eigen::Vector3d InverseQuaternionRotate(const Quaternion &orientation,
                                               const Eigen::Vector3d &rotated) {
  Eigen::Quaternion<double> quaternion(orientation.qw(), orientation.qx(),
                                       orientation.qy(), orientation.qz());
  return static_cast<Eigen::Vector3d>(quaternion.toRotationMatrix().inverse() *
                                      rotated);
}

/**
 * @brief Compute the relative pose of B in A's coordinate frame
 *
 * The relative transform is computed as: A^{-1} * B
 *
 * @param A Global transform of frame A
 * @param B Global transform of frame B
 * @return Transform of B in A's local frame
 */
inline Eigen::Isometry3d ComputeRelativePose(const Eigen::Isometry3d &A,
                                             const Eigen::Isometry3d &B) {
  return A.inverse() * B;
}

/**
 * @brief Helper to construct a Eigen::Isometry3d from x, y, z, and heading
 * angle
 *
 * @param x X-coordinate in meters
 * @param y Y-coordinate in meters
 * @param z Z-coordinate in meters
 * @param heading Heading angle in radians (zero at East, counterclockwise
 * positive)
 * @return Eigen::Isometry3d combining translation and yaw rotation
 */
inline Eigen::Isometry3d FromXYHeading(double x, double y, double z,
                                       double heading) {
  Eigen::Isometry3d pose = Eigen::Isometry3d::Identity();
  pose.translation() = Eigen::Vector3d(x, y, z);
  pose.linear() = HeadingToQuaternion(heading).toRotationMatrix();
  return pose;
}

/**
 * @brief Helper to deconstruct an Eigen::Isometry3d into x, y, z, and heading
 * angle. This is the inverse operation of FromXYHeading.
 *
 * @param pose The Eigen::Isometry3d pose to deconstruct.
 * @param x Output reference for X-coordinate in meters.
 * @param y Output reference for Y-coordinate in meters.
 * @param z Output reference for Z-coordinate in meters.
 * @param heading Output reference for Heading angle in radians (zero at East,
 * counterclockwise positive). Note: The heading will be within [-PI, PI].
 */
inline void ToXYHeading(const Eigen::Isometry3d &pose, double &x, double &y,
                        double &z, double &heading) {
  // Extract translation
  x = pose.translation().x();
  y = pose.translation().y();
  z = pose.translation().z();

  // Extract rotation (heading)
  // The heading is the yaw component. We can extract it from the rotation
  // matrix. For a rotation matrix primarily representing yaw (rotation around
  // Z-axis), the yaw angle 'heading' can be found using atan2(R(1,0), R(0,0)).
  // R(0,0) = cos(heading)
  // R(1,0) = sin(heading)
  heading = std::atan2(pose.linear()(1, 0), pose.linear()(0, 0));
}

}  // namespace math
}  // namespace common
}  // namespace apollo
