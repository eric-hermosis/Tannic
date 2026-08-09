enable_testing()

find_package(GTest QUIET)
  
if (NOT GTest_FOUND)
    message(STATUS "Google Test not found, fetching and building")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest) 
endif() 

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(TESTS     
    test-types.cpp
    test-layouts.cpp
    test-symbols.cpp
    test-graph.cpp
)

if (TESTS)  
    foreach(filename ${TESTS})
        get_filename_component(testname ${filename} NAME_WE)
        add_executable(${testname} ${filename})
        target_include_directories(${testname} PRIVATE ../include)
        target_link_libraries     (${testname} PRIVATE Tannic)
        target_link_libraries     (${testname} PUBLIC  GTest::gtest_main)
        add_test(NAME ${testname} COMMAND ${testname})
    endforeach(filename ${TESTS})
endif()