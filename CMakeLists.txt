cmake_minimum_required(VERSION 3.13)
project(homfa-runner)

SET(DENABLE_SPQLIOS_AVX, "off")
SET(DENABLE_SPQLIOS_FMA, "off")

# add_definitions("-std=c++14")
include(${CMAKE_BINARY_DIR}/bin/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bin/TFHEpp)

# include(${CMAKE_SOURCE_DIR}/modules/conanbuildinfo.cmake)


# add_library(graph SHARED src/graph.cpp)

# add_executable(main src/main.cpp)
# add_executable(graph_test test/gtest_main.cpp test/plain_test.cpp)

# find_package(GTest REQUIRED)

# target_link_libraries(main graph ${CONAN_LIBS})
# target_link_libraries(graph_test GTest::gtest graph ${CONAN_LIBS})
# add_test(test graph_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
