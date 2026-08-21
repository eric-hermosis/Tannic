cmake_minimum_required(VERSION 4.2)

project(Tannic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SOURCES   
    src/io.cpp
    src/environments.cpp  
    src/graphs.cpp
    src/expressions.cpp
    src/visitors.cpp
    src/plans.cpp
    src/variables.cpp
    src/operations.cpp
)

add_library(Tannic STATIC ${SOURCES})  
add_executable(main main.cpp) 

target_include_directories(Tannic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(Tannic PUBLIC -freflection)
target_link_libraries(main PRIVATE Tannic)  

option(BUILD_TESTS "Build tests" ON) 

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()