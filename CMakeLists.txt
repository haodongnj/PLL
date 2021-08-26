project(PLL)
cmake_minimum_required(VERSION 3.0)

add_library(PLL STATIC
        src/pll_sogi.c
        src/pll_matlab.c
        src/fll.c
        )

target_include_directories(PLL PRIVATE
        include
        )
