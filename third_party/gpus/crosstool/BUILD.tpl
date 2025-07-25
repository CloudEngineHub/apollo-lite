# This file is expanded from a template by cuda_configure.bzl
# Update cuda_configure.bzl#verify_build_defines when adding new variables.

load(":cc_toolchain_config.bzl", "cc_toolchain_config")

licenses(["restricted"])

package(default_visibility = ["//visibility:public"])

toolchain_type(
    name = "cuda_toolchain_type",
)

toolchain(
    name = "toolchain-linux",
    exec_compatible_with = [
        "@platforms//os:linux",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    toolchain = ":cc-compiler-local",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
    # toolchain_type = ":cuda_toolchain_type",
)

cc_toolchain_suite(
    name = "toolchain",
    toolchains = {
        "local|compiler": ":cc-compiler-local",
        "arm": ":cc-compiler-local",
        "aarch64": ":cc-compiler-local",
        "k8": ":cc-compiler-local",

    },
)

cc_toolchain(
    name = "cc-compiler-local",
    all_files = "%{compiler_deps}",
    compiler_files = "%{compiler_deps}",
    ar_files = "%{compiler_deps}",
    as_files = "%{compiler_deps}",
    dwp_files = ":empty",
    linker_files = "%{compiler_deps}",
    objcopy_files = ":empty",
    strip_files = ":empty",
    # To support linker flags that need to go to the start of command line
    # we need the toolchain to support parameter files. Parameter files are
    # last on the command line and contain all shared libraries to link, so all
    # regular options will be left of them.
    supports_param_files = 1,
    toolchain_identifier = "local_linux",
    toolchain_config = ":cc-compiler-local-config",
)

cc_toolchain_config(
    name = "cc-compiler-local-config",
    cpu = "local",
    builtin_include_directories = [%{cxx_builtin_include_directories}],
    extra_no_canonical_prefixes_flags = [%{extra_no_canonical_prefixes_flags}],
    host_compiler_path = "%{host_compiler_path}",
    host_compiler_prefix = "%{host_compiler_prefix}",
    host_compiler_warnings = [%{host_compiler_warnings}],
    host_unfiltered_compile_flags = [%{unfiltered_compile_flags}],
    linker_bin_path = "%{linker_bin_path}",
    builtin_sysroot = "%{builtin_sysroot}",
    cuda_path = "%{cuda_toolkit_path}",
    compiler = "%{compiler}",
)

filegroup(
    name = "empty",
    srcs = [],
)

filegroup(
    name = "crosstool_wrapper_driver_is_not_gcc",
    srcs = ["clang/bin/crosstool_wrapper_driver_is_not_gcc"],
)
