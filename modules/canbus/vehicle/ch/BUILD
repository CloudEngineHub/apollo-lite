load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ch_vehicle_factory",
    srcs = ["ch_vehicle_factory.cc"],
    hdrs = ["ch_vehicle_factory.h"],
    deps = [
        ":ch_controller",
        ":ch_message_manager",
        "//modules/canbus/vehicle:abstract_vehicle_factory",
    ],
)

cc_library(
    name = "ch_message_manager",
    srcs = ["ch_message_manager.cc"],
    hdrs = ["ch_message_manager.h"],
    deps = [
        "//modules/common_msgs/chassis_msgs:chassis_detail_cc_proto",
        "//modules/canbus/vehicle/ch/protocol:canbus_ch_protocol",
        "//modules/drivers/canbus/can_comm:message_manager_base",
        "//modules/drivers/canbus/common:canbus_common",
    ],
)

cc_library(
    name = "ch_controller",
    srcs = ["ch_controller.cc"],
    hdrs = ["ch_controller.h"],
    deps = [
        ":ch_message_manager",
        "//modules/canbus/proto:canbus_conf_cc_proto",
        "//modules/common_msgs/chassis_msgs:chassis_cc_proto",
        "//modules/canbus/proto:vehicle_parameter_cc_proto",
        "//modules/canbus/vehicle:vehicle_controller_base",
        "//modules/canbus/vehicle/ch/protocol:canbus_ch_protocol",
        "//modules/common_msgs/basic_msgs:error_code_cc_proto",
        "//modules/common_msgs/control_msgs:control_cmd_cc_proto",
    ],
)

cc_test(
    name = "ch_controller_test",
    size = "small",
    srcs = ["ch_controller_test.cc"],
    data = ["//modules/canbus:test_data"],
    deps = [
        ":ch_controller",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "ch_message_manager_test",
    size = "small",
    srcs = ["ch_message_manager_test.cc"],
    deps = [
        "//modules/canbus/vehicle/ch:ch_message_manager",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "ch_vehicle_factory_test",
    size = "small",
    srcs = ["ch_vehicle_factory_test.cc"],
    deps = [
        ":ch_vehicle_factory",
        "@com_google_googletest//:gtest_main",
    ],
)

cpplint()
