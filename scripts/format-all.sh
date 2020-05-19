#!/bin/sh
ROOT=`git rev-parse --show-toplevel`
find "${ROOT}/src/" \( -name \*.cpp -or -name \*.hpp -or -name \*.h \) -exec clang-format -i -style=file "{}" \;