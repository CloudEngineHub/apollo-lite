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

class Hornrpt79 : public ::apollo::drivers::canbus::ProtocolData<
                      ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Hornrpt79();
  void Parse(const std::uint8_t* bytes, int32_t length,
             ChassisDetail* chassis) const override;

 private:
  // config detail: {'name': 'OUTPUT_VALUE', 'enum': {0: 'OUTPUT_VALUE_OFF', 1:
  // 'OUTPUT_VALUE_ON'}, 'precision': 1.0, 'len': 8, 'is_signed_var': False,
  // 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 23, 'type': 'enum',
  // 'order': 'motorola', 'physical_unit': ''}
  Horn_rpt_79::Output_valueType output_value(const std::uint8_t* bytes,
                                             const int32_t length) const;

  // config detail: {'name': 'COMMANDED_VALUE', 'enum': {0:
  // 'COMMANDED_VALUE_OFF', 1: 'COMMANDED_VALUE_ON'}, 'precision': 1.0, 'len':
  // 8, 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[0|1]', 'bit':
  // 15, 'type': 'enum', 'order': 'motorola', 'physical_unit': ''}
  Horn_rpt_79::Commanded_valueType commanded_value(const std::uint8_t* bytes,
                                                   const int32_t length) const;

  // config detail: {'name': 'MANUAL_INPUT', 'enum': {0: 'MANUAL_INPUT_OFF', 1:
  // 'MANUAL_INPUT_ON'}, 'precision': 1.0, 'len': 8, 'is_signed_var': False,
  // 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 7, 'type': 'enum',
  // 'order': 'motorola', 'physical_unit': ''}
  Horn_rpt_79::Manual_inputType manual_input(const std::uint8_t* bytes,
                                             const int32_t length) const;
};

}  // namespace gem
}  // namespace canbus
}  // namespace apollo
