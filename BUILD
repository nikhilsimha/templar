load(
  "@io_bazel_rules_python//python:python.bzl",
  "py_binary", "py_library", "py_test",
)

load("@py_deps//:requirements.bzl", "requirement")

load("//:antlr.bzl", "py_parser_gen")

py_parser_gen(
    name = "hello_parser",
    grammar_file = "grammar/Hello.g4",
)

py_binary(
    name = "translator",
    srcs = [
        "translator.py",
        # "antlr4_grammar/HelloParser.py",
        ":hello_parser",
    ],
    deps = [
        requirement("antlr4-python3-runtime"),
    ],
)



cc_library(
    name = "monoid",
    srcs = [],
    hdrs = ["src/Monoids.hpp", "src/Utils.hpp",],
    deps = [
        "//external:glog",
        "//external:gtest",
        "//external:tdigest",
    ]
)

cc_binary(
    name = "monoid_test",
    srcs = ["src/Monoids.cpp"],
    deps = [
        ":monoid",
    ],
)