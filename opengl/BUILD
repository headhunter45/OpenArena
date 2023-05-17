load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "window",
    srcs = ["window.cpp"],
    hdrs = ["window.h"],
    visibility = ["//visibility:public"],
    deps = ["//:window"],
)

cc_test(
    name = "window_test",
    srcs = ["window_test.cpp"],
    deps = [
        ":window",
        "@TinyTest//:tinytest",
    ],
)
