cmake_minimum_required(VERSION 2.8.12)
project(homfa-runner)

add_definitions("-std=c++14")

include(${CMAKE_SOURCE_DIR}/modules/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(main src/main.cpp src/graph.cpp)
target_link_libraries(main ${CONAN_LIBS})