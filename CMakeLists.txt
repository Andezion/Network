cmake_minimum_required(VERSION 3.29)
project(Lab1_PS)

set(CMAKE_CXX_STANDARD 20)

set(SFML_INCLUDE_DIR C://Library//SFML//SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit//SFML-2.6.2//include)
set(SFML_LIB_DIR C://Library//SFML//SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit//SFML-2.6.2//lib)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

add_executable(Lab1_PS main.cpp
        button_handlers.h
        zadanie1.h
        zadanie2.h
        zadanie3.h
        zadanie4.h)

target_link_libraries(Lab1_PS sfml-graphics sfml-window sfml-system)