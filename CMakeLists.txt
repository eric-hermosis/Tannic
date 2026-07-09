cmake_minimum_required(VERSION 4.2)

project(Tannic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES 
    src/trace.cpp
    src/graph.cpp
    src/execution.cpp
    src/io.cpp 
)

add_library(Tannic STATIC ${SOURCES}) 
add_executable(main main.cpp)

target_include_directories(Tannic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE Tannic)