bazel build :compdb
sed -e "s|__EXEC_ROOT__|`bazel info execution_root`|" bazel-bin/compile_commands.json > compile_commands.json
