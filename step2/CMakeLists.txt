# step2: 給湯ポットの最初のテストケース
cmake_minimum_required(VERSION 3.10)

# Create project
set(ProjectName "pot-controller")
project(${ProjectName})

# Compile option
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
# マクロを使っているとgcdaファイルが更新できなくなったためcppはcoverageをつけずにコンパイルすることにする
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# 以下テスト用実行ファイルの設定
enable_testing()

add_executable(
    controller_test
    test/test.cpp
    test/interface_mock.cpp
    src/controller.c
)

# includeディレクトリの追加。add_executableのあとじゃないといけない
target_include_directories(controller_test PRIVATE ./src)

target_link_libraries(
    controller_test
    GTest::gtest_main
    GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(controller_test)
