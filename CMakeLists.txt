cmake_minimum_required(VERSION 3.20)
project(FIZZ_BUZZ CXX)

if(MSVC)
    # Habilita C++26/latest e o suporte experimental a contratos do MSVC
    add_compile_options(/std:c++latest /experimental:contract)
else()
    set(CMAKE_CXX_STANDARD 26)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

find_package(GTest REQUIRED)

add_executable(Main 
    src/main.cpp
    src/fizz_buzz.cpp
    src/contract_handler.cpp
)

target_include_directories(Main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(RunTests
    src/fizz_buzz.cpp
    src/contract_handler.cpp
    tests/tests.cpp
)

target_include_directories(RunTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(RunTests PRIVATE GTest::gtest GTest::gtest_main)
