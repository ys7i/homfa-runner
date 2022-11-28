add_executable(main ${CMAKE_BINARY_DIR}/src/main.cpp)
add_library(graph SHARED ${CMAKE_BINARY_DIR}/src/graph/graph.cpp ${CMAKE_BINARY_DIR}/src/graph/forward-graph.cpp ${CMAKE_BINARY_DIR}/src/graph/reverse-graph.cpp)
target_link_libraries(graph tfhe++)
target_include_directories(graph
  PUBLIC ${CMAKE_BINARY_DIR}/src/graph
)
target_link_libraries(main graph ${CONAN_LIBS} tfhe++)