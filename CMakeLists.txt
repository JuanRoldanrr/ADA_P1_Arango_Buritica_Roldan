cmake_minimum_required(VERSION 3.20)
project(ada_p1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ada_p1
    src/main.cpp
    src/fb_runner.cpp
    src/fb_bruteforce.cpp
)

add_executable(fb_tests
    tests/fb_tests.cpp
    src/fb_bruteforce.cpp
)

add_executable(verificar_semilla resources/seed.cpp)
