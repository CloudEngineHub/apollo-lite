/******************************************************************************
 * Copyright 2020 The Apollo Authors. All Rights Reserved.
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
namespace neolix_edu {

class Aebdiagnosis1626 : public ::apollo::drivers::canbus::ProtocolData<
                             ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Aebdiagnosis1626();
  void Parse(const std::uint8_t* bytes, int32_t length,
             ChassisDetail* chassis) const override;

 private:
  // config detail: {'name': 'AEB_SoftwareVersion', 'offset': 0.0,
  // 'precision': 1.0, 'len': 8, 'is_signed_var': False, 'physical_range':
  // '[0.0|255.0]', 'bit': 55, 'type': 'double', 'order': 'motorola',
  // 'physical_unit': 'bit'}
  double aeb_softwareversion(const std::uint8_t* bytes,
                             const int32_t length) const;

  // config detail: {'name': 'AEB_HardwareVersion', 'offset': 0.0,
  // 'precision': 1.0, 'len': 8, 'is_signed_var': False, 'physical_range':
  // '[0.0|255.0]', 'bit': 63, 'type': 'double', 'order': 'motorola',
  // 'physical_unit': 'bit'}
  double aeb_hardwareversion(const std::uint8_t* bytes,
                             const int32_t length) const;
};

}  // namespace neolix_edu
}  // namespace canbus
}  // namespace apollo
