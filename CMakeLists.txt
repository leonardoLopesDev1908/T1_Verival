cmake_minimum_required(VERSION 3.20)
project(FIZZ_BUZZ CXX)

if(MSVC)
    add_compile_options(/std:c++latest)
else()
    set(CMAKE_CXX_STANDARD 26)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_executable(Main 
    src/main.cpp
    src/fizz_buzz.cpp
)

target_include_directories(Main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)