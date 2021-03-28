package(default_visibility = ["//visibility:public"])

cc_library(
    name = "caches",
    srcs = ["src/libs/cache.cpp"],
    hdrs = ["src/include/cache.h"],
)

cc_binary(
    name = "tertiary_func",
    srcs = ["app/tertiary_func.cpp"],
    copts = ["-Isrc/include/"],
)

cc_test(
    name = "test/cache.cpp",
    srcs = ["hello-world.cc"],
    deps = [":caches"],
)

cc_test(
    name = "strings",
    srcs = ["app/strings.cpp"],
)

filegroup(
    name = "include",
    srcs = glob(["src/include/*.h"])
)

