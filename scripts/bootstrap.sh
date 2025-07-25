#!/usr/bin/env bash

###############################################################################
# Copyright 2017-2021 The Apollo Authors. All Rights Reserved.
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

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Todo(daohu527): The gflags parameter server_ports is passed in through
# the command line, and then transparently passed to the dreamview startup
# parameter. Since cyber_launch does not take parameters,
# it is necessary to discuss whether to add parameter functions in cyber_launch.
# Read server_ports from modules/common/data/global_flagfile.txt
DREAMVIEW_URL="http://localhost:8888"

GLOBAL_FLAGFILE="${DIR}/../modules/common/data/global_flagfile.txt"
if [[ -f "$GLOBAL_FLAGFILE" ]]; then
  SERVER_PORT=$(grep -E '^--server_ports=' "$GLOBAL_FLAGFILE" | head -n1 | cut -d'=' -f2 | cut -d',' -f1)
  if [[ -n "$SERVER_PORT" ]]; then
    DREAMVIEW_URL="http://localhost:${SERVER_PORT}"
  fi
fi

echo "DREAMVIEW_URL is set to ${DREAMVIEW_URL}"

cd "${DIR}/.."

# Make sure supervisord has correct coredump file limit.
ulimit -c unlimited

source "${DIR}/apollo_base.sh"

function start() {
  for mod in ${APOLLO_BOOTSTRAP_EXTRA_MODULES}; do
    echo "Starting ${mod}"
    nohup cyber_launch start ${mod} &
  done
  ./scripts/monitor.sh start
  ./scripts/dreamview.sh start
  if [ $? -eq 0 ]; then
    sleep 2 # wait for some time before starting to check
    http_status="$(curl -o /dev/null -x '' -I -L -s -w '%{http_code}' ${DREAMVIEW_URL})"
    if [ $http_status -eq 200 ]; then
      echo "Dreamview is running at" $DREAMVIEW_URL
    else
      echo "Failed to start Dreamview. Please check /apollo/nohup.out or /apollo/data/core for more information"
    fi
  fi
}

function stop() {
  ./scripts/dreamview.sh stop
  ./scripts/monitor.sh stop
  for mod in ${APOLLO_BOOTSTRAP_EXTRA_MODULES}; do
    echo "Stopping ${mod}"
    nohup cyber_launch stop ${mod}
  done
}

case $1 in
  start)
    start
    ;;
  stop)
    stop
    ;;
  restart)
    stop
    start
    ;;
  *)
    start
    ;;
esac
