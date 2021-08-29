project(test_sogi_pll)
cmake_minimum_required(VERSION 3.10.0)

add_executable(test_sogi_pll 
	test_sogi_pll.c
	../../src/pll_sogi.c)

target_include_directories(test_sogi_pll PRIVATE ../../include)
target_link_libraries(test_sogi_pll m)
