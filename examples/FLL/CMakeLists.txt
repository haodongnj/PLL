project(test_fll)
cmake_minimum_required(VERSION 3.10.0)

add_executable(test_fll
        test_fll.c
        ../../src/fll.c)

target_include_directories(test_fll PRIVATE ../../include)
if (UNIX)
    target_link_libraries(test_fll PRIVATE m)
endif (UNIX)