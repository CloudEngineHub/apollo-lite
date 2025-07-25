#!/usr/bin/env bash

###############################################################################
# Copyright 2020 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

# Fail on first error.
set -e
MY_MODE="$1"

CURR_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
. ${CURR_DIR}/installer_base.sh

bash ${CURR_DIR}/install_opencv.sh
bash ${CURR_DIR}/install_proj.sh
bash ${CURR_DIR}/install_openh264.sh
bash ${CURR_DIR}/install_ffmpeg.sh

# Required by Python audio driver
# apt_get_update_and_install \
#     python3-pyaudio \
#     portaudio19-dev

# Required by LiDAR drivers for packets captured via pcap
apt_get_update_and_install \
    libpcap-dev

# Clean up cache to reduce layer size.
apt-get clean && \
    rm -rf /var/lib/apt/lists/*
