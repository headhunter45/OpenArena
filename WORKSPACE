load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
# To update config run `bazel run @hedron_compile_commands//:refresh_all`
http_archive(
    name = "hedron_compile_commands",
    sha256 = "99bc3106eb6ce5ffab3c31de8501d4d628de5f1acd74b8b563a876bd39a2e32f",
    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    strip_prefix = "bazel-compile-commands-extractor-b33a4b05c2287372c8e932c55ff4d3a37e6761ed",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/b33a4b05c2287372c8e932c55ff4d3a37e6761ed.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

http_archive(
    name = "com_google_googletest",
    sha256 = "d0491ad8a4f6d4dadbc33229a0a1c4bfd3b61a750411b69c4945acd5cbb6d73f",
    strip_prefix = "googletest-ccdeec888ebb740a7ea4e07d3e84a1b7ee32b315",
    urls = ["https://github.com/google/googletest/archive/ccdeec888ebb740a7ea4e07d3e84a1b7ee32b315.zip"],
)

http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-b971ac5250ea8de900eae9f95e06548d14cd95fe",
    urls = ["https://github.com/abseil/abseil-cpp/archive/b971ac5250ea8de900eae9f95e06548d14cd95fe.zip"],
)

http_archive(
    name = "TinyTest",
    sha256 = "d6729abbec6ac167635be7463d8c37ca54b08e506e61553236b50c5ad30e8736",
    strip_prefix = "TinyTest-a4109d2f494fd3fd3cc47069239fd3c79f728d5a",
    urls = ["https://github.com/headhunter45/TinyTest/archive/a4109d2f494fd3fd3cc47069239fd3c79f728d5a.zip"],
)

http_archive(
    name = "CPPUtils",
    sha256 = "f6464f02ba6c67e36058c3f6f06ff7fe3977340af3fdd350153f4aa15c628a6a",
    strip_prefix = "cpp-utils-e05fb1e0a4e6ba247a8cd4af13a3aefa23e456dd",
    urls = ["https://github.com/headhunter45/cpp-utils/archive/e05fb1e0a4e6ba247a8cd4af13a3aefa23e456dd.zip"],
)
