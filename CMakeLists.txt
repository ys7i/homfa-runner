cmake_minimum_required(VERSION 3.13)
project(homfa-runner)
enable_testing()

add_definitions("-std=c++14")

include(${CMAKE_SOURCE_DIR}/modules/conanbuildinfo.cmake)
conan_basic_setup()

add_library(graph src/graph.cpp)

add_executable(main src/main.cpp)
add_executable(graph_test test/gtest_main.cpp test/plain_test.cpp)

find_package(GTest REQUIRED)

target_link_libraries(main graph ${CONAN_LIBS})
target_link_libraries(graph_test GTest::gtest)
# add_test(test graph_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
