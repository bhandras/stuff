load("@bazel-compilation-database//:aspects.bzl", "compilation_database")

compilation_database(
    name = "compdb",
    testonly = 1,
    targets = [
        "//src:brandes",
        "//src:brandes_test",
    ],
)
