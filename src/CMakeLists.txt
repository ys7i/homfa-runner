add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_library(graph SHARED ${CMAKE_SOURCE_DIR}/src/graph/graph.cpp ${CMAKE_SOURCE_DIR}/src/graph/forward-graph.cpp ${CMAKE_SOURCE_DIR}/src/graph/reverse-graph.cpp ${CMAKE_SOURCE_DIR}/src/graph/utils.cpp)
target_link_libraries(graph tfhe++ ${CONAN_LIBS})
target_include_directories(graph
  PUBLIC ${CMAKE_SOURCE_DIR}/src/graph
)
target_link_libraries(main graph ${CONAN_LIBS} tfhe++)