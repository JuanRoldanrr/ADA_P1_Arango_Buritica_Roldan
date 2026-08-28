cmake_minimum_required(VERSION 3.20)

project(ada_p1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ada_p1
    src/main.cpp

    # Fuerza Bruta
    src/fb_runner.cpp
    src/fb_bruteforce.cpp

    # Backtracking
    src/bt_runner.cpp
    src/bt_backtracking.cpp
    src/bt_sin_poda.cpp
)

# Tests de Fuerza Bruta
add_executable(fb_tests
    tests/fb_tests.cpp
    src/fb_bruteforce.cpp
)

# Tests de Backtracking
add_executable(bt_tests
    tests/bt_tests.cpp
    src/bt_backtracking.cpp
    src/bt_sin_poda.cpp
)

# Verificación de semilla
add_executable(verificar_semilla
    resources/seed.cpp
)