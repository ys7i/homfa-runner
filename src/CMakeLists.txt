add_executable(main ${CMAKE_BINARY_DIR}/src/main.cpp)
add_library(graph SHARED ${CMAKE_BINARY_DIR}/src/graph.cpp)
target_include_directories(graph
  PUBLIC ${CMAKE_BINARY_DIR}/src
)
target_link_libraries(main graph ${CONAN_LIBS})