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