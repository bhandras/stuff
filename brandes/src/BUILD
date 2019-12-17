package(default_visibility = ["//visibility:public"])

cc_library(
    name = "brandes",
    srcs = ["brandes.cc"],
    hdrs = ["brandes.h"],
    deps = [
        "@abseil-cpp//absl/strings",
    ],
)

cc_test(
    name = "brandes_test",
    srcs = ["brandes_test.cc"],
    deps = [
        ":brandes",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
