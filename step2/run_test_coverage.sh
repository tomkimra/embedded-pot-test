#!/bin/sh
DIR=./CMakeFiles/controller_test.dir/src
cd build
lcov --directory $DIR --zerocounters
ctest --output-on-failure
lcov -d $DIR -c -o coverage.info
genhtml -o . coverage.info
