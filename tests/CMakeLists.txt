cmake_minimum_required(VERSION 3.16)

# Name the project `IWC++Testing`.
project(IWC++Testing LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# Dependencies declaration and fetching.
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  git
  GIT_TAG        v3.7.1
)

FetchContent_MakeAvailable(Catch2)

#
# Define source files(srcFiles).
#
add_library(srcFiles ../src/iwcpp.cpp ../src/parser.cpp ../src/eval.cpp ../src/lexer.cpp)
# See https://stackoverflow.com/questions/41814426/cmake-cant-find-header-files
target_include_directories(srcFiles PUBLIC ./)
target_compile_features(srcFiles PUBLIC cxx_std_17)


add_executable(iwcpp ../src/main.cpp)

# Linking main to the srcFiles library
target_link_libraries(iwcpp srcFiles)

# adding tests
add_executable(tests tests.cpp)
target_link_libraries(tests srcFiles Catch2::Catch2WithMain)