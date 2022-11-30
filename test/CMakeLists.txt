enable_testing()

add_executable(graph_test ${CMAKE_SOURCE_DIR}/test/gtest_main.cpp ${CMAKE_SOURCE_DIR}/test/plain_test.cpp ${CMAKE_SOURCE_DIR}/test/offline_test.cpp)
target_include_directories(graph_test PUBLIC ${CMAKE_SOURCE_DIR}/src/graph)
find_package(GTest REQUIRED)
target_link_libraries(graph_test GTest::gtest graph)
add_test(test graph_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR})