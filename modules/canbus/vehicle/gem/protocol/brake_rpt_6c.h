/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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

#pragma once

#include "modules/common_msgs/chassis_msgs/chassis_detail.pb.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace gem {

class Brakerpt6c : public ::apollo::drivers::canbus::ProtocolData<
                       ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Brakerpt6c();
  void Parse(const std::uint8_t* bytes, int32_t length,
             ChassisDetail* chassis) const override;

 private:
  // config detail: {'name': 'MANUAL_INPUT', 'offset': 0.0, 'precision': 0.001,
  // 'len': 16, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 7,
  // 'type': 'double', 'order': 'motorola', 'physical_unit': '%'}
  double manual_input(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'COMMANDED_VALUE', 'offset': 0.0, 'precision':
  // 0.001, 'len': 16, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit':
  // 23, 'type': 'double', 'order': 'motorola', 'physical_unit': '%'}
  double commanded_value(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'OUTPUT_VALUE', 'offset': 0.0, 'precision': 0.001,
  // 'len': 16, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 39,
  // 'type': 'double', 'order': 'motorola', 'physical_unit': '%'}
  double output_value(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'BRAKE_ON_OFF', 'enum': {0: 'BRAKE_ON_OFF_OFF', 1:
  // 'BRAKE_ON_OFF_ON'}, 'precision': 1.0, 'len': 1, 'is_signed_var': False,
  // 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 48, 'type': 'enum',
  // 'order': 'motorola', 'physical_unit': ''}
  Brake_rpt_6c::Brake_on_offType brake_on_off(const std::uint8_t* bytes,
                                              const int32_t length) const;
};

}  // namespace gem
}  // namespace canbus
}  // namespace apollo
