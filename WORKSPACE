git_repository(
    name = "io_bazel_rules_python",
    remote = "https://github.com/bazelbuild/rules_python.git",
    # NOT VALID!  Replace this with a Git commit SHA.
    commit = "72ca7ba07cf2543d71c608d5473159553cb38660",
)

# Only needed for PIP support:
load("@io_bazel_rules_python//python:pip.bzl", "pip_repositories", "pip_import")

pip_repositories()

pip_import(
   name = "py_deps",
   requirements = "//:requirements.txt",
)

# Load the pip_install symbol for my_deps, and create the dependencies'
# repositories.
load("@py_deps//:requirements.bzl", "pip_install")
pip_install()

# download antlr4
http_file(
    name = "antlr4_complete_jar",
    url = "https://www.antlr.org/download/antlr-4.7.1-complete.jar",
    executable = True,
)




#glog + gtest + gflags
git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tag = "v2.2.2"
)

git_repository(
    name = "com_github_glog_glog",
    remote = "https://github.com/google/glog.git",
    tag = "v0.4.0"
)

git_repository(
    name = "com_github_google_googletest",
    remote = "https://github.com/google/googletest.git",
    tag = "release-1.8.1"
)

bind(
    name = "glog",
    actual = "@com_github_glog_glog//:glog",
)

bind(
    name = "gtest",
    actual = "@com_github_google_googletest//:gtest",
)