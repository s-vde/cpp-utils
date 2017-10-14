cmake_minimum_required(VERSION 3.5)

project(cpp_utils_test)

set(CMAKE_CXX_STANDARD 14)


####################
# DEPENDENCIES

include_directories(${GOOGLE_TEST}/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)


####################
# LIBRARY

add_executable(CppUtilsTest
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/fork.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main_TEST.cpp
)


####################
# LINKING

target_link_libraries(CppUtilsTest gtest)
