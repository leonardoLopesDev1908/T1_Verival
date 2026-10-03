cmake_mininum_required(VERSION 3.24)
project(T1_Verival)

target_include_directories(${CMAKE_CURRENT_DIR}/include)

add_executable(Main ${CMAKE_CURRENT_DIR}/src/main.cpp);
