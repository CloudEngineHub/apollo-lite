## Auto generated by `proto_build_generator.sh`
load("@com_google_protobuf//bazel:proto_library.bzl", "proto_library")
load("@com_google_protobuf//bazel:cc_proto_library.bzl", "cc_proto_library")
load("@com_google_protobuf//bazel:py_proto_library.bzl", "py_proto_library")

package(default_visibility = ["//visibility:public"])

cc_proto_library(
    name = "sins_pva_cc_proto",
    deps = [
        ":sins_pva_proto",
    ],
)

proto_library(
    name = "sins_pva_proto",
    srcs = ["sins_pva.proto"],
    deps = [
        "//modules/common_msgs/basic_msgs:geometry_proto",
        "//modules/common_msgs/basic_msgs:header_proto",
    ],
)

py_proto_library(
    name = "sins_pva_py_pb2",
    deps = [":sins_pva_proto"],
)

cc_proto_library(
    name = "localization_config_cc_proto",
    deps = [
        ":localization_config_proto",
    ],
)

proto_library(
    name = "localization_config_proto",
    srcs = ["localization_config.proto"],
)

py_proto_library(
    name = "localization_config_py_pb2",
    deps = [":localization_config_proto"],
)

cc_proto_library(
    name = "gnss_pnt_result_cc_proto",
    deps = [
        ":gnss_pnt_result_proto",
    ],
)

proto_library(
    name = "gnss_pnt_result_proto",
    srcs = ["gnss_pnt_result.proto"],
    deps = [
        "//modules/common_msgs/sensor_msgs:gnss_raw_observation_proto",
    ],
)

py_proto_library(
    name = "gnss_pnt_result_py_pb2",
    deps = [":gnss_pnt_result_proto"],
)

cc_proto_library(
    name = "rtk_config_cc_proto",
    deps = [
        ":rtk_config_proto",
    ],
)

proto_library(
    name = "rtk_config_proto",
    srcs = ["rtk_config.proto"],
)

py_proto_library(
    name = "rtk_config_py_pb2",
    deps = [":rtk_config_proto"],
)

cc_proto_library(
    name = "measure_cc_proto",
    deps = [
        ":measure_proto",
    ],
)

proto_library(
    name = "measure_proto",
    srcs = ["measure.proto"],
    deps = [
        "//modules/common_msgs/basic_msgs:geometry_proto",
        "//modules/common_msgs/basic_msgs:header_proto",
    ],
)

py_proto_library(
    name = "measure_py_pb2",
    deps = [":measure_proto"],
)
