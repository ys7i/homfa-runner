enable_testing()

add_executable(graph_test ${CMAKE_BINARY_DIR}/test/gtest_main.cpp ${CMAKE_BINARY_DIR}/test/plain_test.cpp)
find_package(GTest REQUIRED)
target_link_libraries(graph_test GTest::gtest graph ${CONAN_LIBS})
add_test(test graph_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin )