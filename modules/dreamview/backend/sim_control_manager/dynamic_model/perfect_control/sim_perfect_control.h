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
 */

#pragma once

#include <memory>
#include <random>

#include "gtest/gtest_prod.h"

#include "modules/common_msgs/localization_msgs/localization.pb.h"
#include "modules/common_msgs/planning_msgs/navigation.pb.h"
#include "modules/common_msgs/planning_msgs/planning.pb.h"
#include "modules/common_msgs/prediction_msgs/prediction_obstacle.pb.h"

#include "cyber/cyber.h"
#include "modules/dreamview/backend/common/dreamview_gflags.h"
#include "modules/dreamview/backend/map/map_service.h"
#include "modules/dreamview/backend/sim_control_manager/core/sim_control_base.h"

/**
 * @namespace apollo::dreamview
 * @brief apollo::dreamview
 */
namespace apollo {
namespace dreamview {

/**
 * @class SimPerfectControl
 * @brief A module that simulates a 'perfect control' algorithm, which assumes
 * an ideal world where the car can be perfectly placed wherever the planning
 * asks it to be, with the expected speed, acceleration, etc.
 */
class SimPerfectControl final : public SimControlBase {
 public:
  /**
   * @brief Constructor of SimPerfectControl.
   * @param map_service the pointer of MapService.
   */
  explicit SimPerfectControl(const MapService *map_service);

  /**
   * @brief setup callbacks and timer
   * @param set_start_point initialize localization.
   */
  void Init(bool set_start_point, nlohmann::json start_point_attr,
            bool use_start_point_position = false) override;

  /**
   * @brief Starts the timer to publish simulated localization and chassis
   * messages.
   */
  void Start() override;

  /**
   * @brief Stops the timer.
   */
  void Stop() override;

  /**
   * @brief Resets the internal state.
   */
  void Reset() override;

  void RunOnce() override;

 private:
  void OnPlanning(
      const std::shared_ptr<apollo::planning::ADCTrajectory> &trajectory);
  void OnRoutingResponse(
      const std::shared_ptr<apollo::routing::RoutingResponse> &routing);
  void OnRoutingRequest(
      const std::shared_ptr<apollo::routing::RoutingRequest> &routing_request);
  void OnReceiveNavigationInfo(
      const std::shared_ptr<apollo::relative_map::NavigationInfo>
          &navigation_info);
  void OnPredictionObstacles(
      const std::shared_ptr<apollo::prediction::PredictionObstacles>
          &obstacles);

  /**
   * @brief Predict the next trajectory point using perfect control model
   */
  bool PerfectControlModel(
      apollo::common::TrajectoryPoint *point,
      apollo::canbus::Chassis::GearPosition *gear_position);

  void PublishChassis(double cur_speed,
                      apollo::canbus::Chassis::GearPosition gear_position);

  void PublishLocalization(
      const apollo::common::TrajectoryPoint &point,
      std::shared_ptr<apollo::localization::LocalizationEstimate> local_ptr);

  void PublishDummyPrediction();

  void InitTimerAndIO();

  void FillCommonLocalizationData(
      const apollo::common::TrajectoryPoint &point,
      std::shared_ptr<apollo::localization::LocalizationEstimate> local_ptr,
      double x, double y, double z, double theta);
  /**
   * @brief Starts the timer to publish simulated localization and chassis
   * messages. Designated Start point for scenario
   */
  void Start(double x, double y) override;

  void InitStartPoint(double start_velocity, double start_acceleration);

  // use scenario start point to init start point under the simulation
  // condition.
  void InitStartPoint(double x, double y, double start_velocity,
                      double start_acceleration);

  // Reset the start point, which can be a dummy point on the map, a current
  // localization pose, or a start position received from the routing module.
  void SetStartPoint(const apollo::common::TrajectoryPoint &point);

  void Freeze();

  void ClearPlanning();

  void InternalReset();

  void InitRandomGenerators(double pos_std_dev_x, double pos_std_dev_y,
                            double pos_std_dev_z, double heading_std_dev);

 private:
  const MapService *map_service_ = nullptr;

  std::unique_ptr<cyber::Node> node_;

  std::shared_ptr<cyber::Reader<apollo::localization::LocalizationEstimate>>
      localization_reader_;
  std::shared_ptr<cyber::Reader<apollo::planning::ADCTrajectory>>
      planning_reader_;
  std::shared_ptr<cyber::Reader<apollo::routing::RoutingResponse>>
      routing_response_reader_;
  std::shared_ptr<cyber::Reader<apollo::routing::RoutingRequest>>
      routing_request_reader_;
  std::shared_ptr<cyber::Reader<apollo::relative_map::NavigationInfo>>
      navigation_reader_;
  std::shared_ptr<cyber::Reader<apollo::prediction::PredictionObstacles>>
      prediction_reader_;

  std::shared_ptr<cyber::Writer<apollo::localization::LocalizationEstimate>>
      localization_writer_;
  std::shared_ptr<cyber::Writer<apollo::canbus::Chassis>> chassis_writer_;
  std::shared_ptr<cyber::Writer<apollo::prediction::PredictionObstacles>>
      prediction_writer_;

  // The timer to publish simulated localization and chassis messages.
  std::unique_ptr<cyber::Timer> sim_control_timer_;

  // The timer to publish dummy prediction
  std::unique_ptr<cyber::Timer> sim_prediction_timer_;

  // Time interval of the timer, in milliseconds.
  static constexpr double kSimControlIntervalMs = 10;
  static constexpr double kSimPredictionIntervalMs = 100;

  // The latest received planning trajectory.
  std::shared_ptr<apollo::planning::ADCTrajectory> current_trajectory_;
  // The index of the previous and next point with regard to the
  // current_trajectory.
  int prev_point_index_ = 0;
  int next_point_index_ = 0;

  // Whether there's a planning received after the most recent routing.
  bool received_planning_ = false;

  // Whether planning has requested a re-routing.
  bool re_routing_triggered_ = false;

  // Whether start point is initialized from actual localization data
  bool start_point_from_localization_ = false;

  // Whether to send dummy predictions
  bool send_dummy_prediction_ = true;

  // The header of the routing planning is following.
  apollo::common::Header current_routing_header_;

  apollo::common::TrajectoryPoint prev_point_;
  apollo::common::TrajectoryPoint next_point_;

  common::PathPoint adc_position_;

  std::mt19937 random_engine_;
  std::normal_distribution<double> pos_noise_x_;
  std::normal_distribution<double> pos_noise_y_;
  std::normal_distribution<double> pos_noise_z_;
  std::normal_distribution<double> heading_noise_;

  apollo::routing::ParkingInfo *parking_info_;

  bool need_calc_origin_;
  Eigen::Isometry3d origin_;

  // Linearize reader/timer callbacks and external operations.
  std::mutex mutex_;

  FRIEND_TEST(SimControlTest, Test);
  FRIEND_TEST(SimControlTest, TestDummyPrediction);
};

}  // namespace dreamview
}  // namespace apollo
