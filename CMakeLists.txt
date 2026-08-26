cmake_minimum_required(VERSION 3.20)
project(ada_p1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ada_p1
        src/main.cpp
        src/bt_runner.cpp
        src/bt_backtracking.cpp
        src/bt_sin_poda.cpp
)

add_executable(bt_tests
        tests/bt_tests.cpp
        src/bt_backtracking.cpp
        src/bt_sin_poda.cpp
)

add_executable(verificar_semilla resources/seed.cpp)