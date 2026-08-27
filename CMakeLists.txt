cmake_minimum_required(VERSION 3.20)
project(ada_p1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable principal del proyecto (incluye tu parte y la de tu compañero)
add_executable(ada_p1
    src/main.cpp
    src/fb_runner.cpp
    src/fb_bruteforce.cpp
)

# Pruebas del módulo Backtracking (Compañero)
add_executable(bt_tests
    tests/bt_tests.cpp
)

# Pruebas del módulo Fuerza Bruta (Tu parte)
add_executable(fb_tests
    tests/fb_tests.cpp
)

# Verificador de Semilla
add_executable(verificar_semilla resources/seed.cpp)
