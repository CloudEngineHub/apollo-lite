load("@rules_cc//cc:defs.bzl", "cc_library")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "engine",
    srcs = [
        "visualization_engine.cc",
        "visualization_manager.cc",
    ],
    hdrs = [
        "visualization_engine.h",
        "visualization_manager.h",
    ],
    copts = [
        "-O2",
        "-DMODULE_NAME=\\\"localization_visualizer\\\"",
    ],
    deps = [
        "//cyber",
        "//modules/common/util",
        "//modules/common/util:util_tool",
        "//modules/localization/msf/common/io:common_io",
        "//modules/localization/msf/local_pyramid_map/base_map",
        "@boost.filesystem",
        "@opencv//:highgui",
    ],
)

cpplint()
