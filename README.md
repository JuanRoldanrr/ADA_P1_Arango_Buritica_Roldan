# Práctica 1 — Fuerza Bruta y Backtracking

## Integrantes

- Viviana Arango Tabares
- Manuela Buriticá Guzmán
- Juan José Roldán

---

Proyecto correspondiente a la Práctica 1 de Análisis y Diseño de Algoritmos de la Universidad EAFIT.

El proyecto implementa dos estrategias de búsqueda:

- **Fuerza Bruta**, para la búsqueda de contraseñas mediante hashes SHA-256.
- **Backtracking**, con una versión con poda y otra sin poda para comparar su comportamiento.

También se incluyen pruebas automatizadas, instancias de prueba, datos experimentales, un diccionario de candidatos y gráficas de resultados.

---

## Estructura

```text
src/
├── bt_policy.hpp          # Alfabeto, categorías, factibilidad y validación de política
├── bt_backtracking.*      # Backtracking con poda
├── bt_sin_poda.*          # Enumeración exhaustiva sin poda
├── bt_runner.*            # Ejecución y experimentación de Backtracking
├── fb_bruteforce.*        # Fuerza Bruta y ataque por diccionario
├── fb_runner.*            # Ejecución del módulo de Fuerza Bruta
├── main.cpp               # Punto de entrada de ambos módulos
└── third_party/
    └── picosha2.h         # Biblioteca utilizada para SHA-256

tests/
├── bt_tests.cpp           # Pruebas automatizadas de Backtracking
└── fb_tests.cpp           # Pruebas automatizadas de Fuerza Bruta

resources/
├── seed.cpp               # Verificación de la semilla del equipo
├── verificar_semilla.cpp  # Verificación de instancias/parámetros
└── diccionario.txt        # Diccionario sintético de 500 candidatos

results/
├── bt_resultados.csv
├── fb_resultados.csv
└── gráficas de experimentación

scripts/
└── scripts utilizados para generar las gráficas

CMakeLists.txt
README.md
```

---

## Compilación

### Opción 1 - CMake

Desde la carpeta raíz, en la terminal
```bash
cmake -S . -B build
cmake --build build
```

### Opción 2 - Compilación manual

Copiar y pegar cada comando en la terminal

```bash
g++ -std=c++17 -O2 -o ada_p1 \
src/main.cpp \
src/bt_runner.cpp \
src/bt_backtracking.cpp \
src/bt_sin_poda.cpp \
src/fb_runner.cpp \
src/fb_bruteforce.cpp
```

Para las pruebas de **Backtracking**

```bash
g++ -std=c++17 -O2 -o bt_tests \
tests/bt_tests.cpp \
src/bt_backtracking.cpp \
src/bt_sin_poda.cpp
```

Para las pruebas de **Fuerza Bruta**

```bash
g++ -std=c++17 -O2 -o fb_tests \
tests/fb_tests.cpp \
src/fb_bruteforce.cpp
```
---

## Ejecución

### Verificación de la semilla

```bash
./build/verificar_semilla
```

La semilla utilizada por el equipo es **2123**

### Backtracking

```bash
./build/ada_p1 bt
```
Este módulo ejecuta las instancias de verificación y las diferentes configuraciones de Backtracking, comparando las versiones con y sin poda.

### Fuerza Bruta

```bash
./build/ada_p1 fb
```

El programa solicita (colocar manualmente):
- Hash objetivo
- Alfabeto (A1/A2)
- Longitud

y ejecuta Fuerza Bruta y ataque por diccionario para la instancia indicada.

### Ayuda (opcional)

```bash
./build/ada_p1 --help
```

---

## Pruebas automatizadas

### Backtracking

```bash
./build/bt_tests
```
Las pruebas verifican estos aspectos:
- Políticas imposibles.
- Coincidencia entre las soluciones obtenidas con y sin poda.
- Reducción de nodos explorados.
- Cumplimiento de las restricciones.
- generación de ejemplos válidos.

### Fuerza Bruta

```bash
./build/fb_tests
```
Las pruebas verifican:
- Búsqueda exitosa con A1
- Búsqueda fallida
- Búsqueda con A2
- Ataque de diccionario exitoso
- Ataque de diccionario fallido
- Archivo de diccionario inexistente
- Conteo de evaluaciones.

---

## Módulo de Fuerza Bruta

### Alfabetos

**A1**

```text
abcdefghijklmnopqrstuvwxyz
```
Tamaño: 26 caracteres.

Longitudes permitidas:

```text
n = 3, 4, 5, 6
```

**A2**

```text
abcdefghijklmnopqrstuvwxyz0123456789
```
Tamaño: 36 caracteres.

Longitudes permitidas:

```text
n = 3, 4, 5
```

El espacio de búsqueda es:

```
A1 → 26^n
A2 → 36^n
```

Para cada candidato se calcula su hash SHA-256 y se compara con el hash objetivo.

### Instancias de FB

Las cinco instancias propias del equipo fueron generadas a partir de la semilla **2123**.

| Instancia | Alfabeto | n | Clave |
|---|---|---:|---|
| objetivo_1 | A1 | 4 | `ijax` |
| objetivo_2 | A2 | 4 | `ans9` |
| objetivo_3 | A1 | 5 | `uxyby` |
| objetivo_4 | A2 | 5 | `r0la7` |
| objetivo_5 | A1 | 6 | `wpctwv` |

### Hashes SHA-256

| Instancia | SHA-256 |
|---|---|
| objetivo_1 | `c56d1270821c92b3205d36e89d1fb0fd0bad3b9f2862242d6b2a5a3392a6b499` |
| objetivo_2 | `b55df863e210fa4784207934f751b2342a6f1f59f63c5f0fabbca7a9f9fba7fa` |
| objetivo_3 | `3d703d21cf2e0792a465caf7e59b6e80b65fe53d90cea94fab66e40ebf663242` |
| objetivo_4 | `199d6d898dfc43886d05ba5540f3da1e42d56c66327de37f67fc981889962c1d` |
| objetivo_5 | `1bc54ae0767a4dba59cb26bb16c4148d058d9a0d7b628340576f4c054432b96d` |

### Instancia de referencia

```text
Clave: abc12
Alfabeto: A2
n: 5
SHA-256:
8d51feb34e3e69f6fa6dffc577e2c60490cf9a7fcd835f9f6af1505b71d74773
```

### Diccionario

El módulo incluye un diccionario sintético de **500 candidatos** ubicado en:

```text
resources/diccionario.txt
```
El ataque por diccionario compara el hash objetivo únicamente con las palabras contenidas en este archivo.

---

## Módulo de Backtracking

El módulo cuenta con dos versiones:
- **Con poda:** utiliza comprobaciones de factibilidad para descartar ramas que no pueden producir soluciones válidas.
- **Sin poda:** recorre el espacio completo y verifica la política al completar cada cadena.
Las pruebas y experimentos comparan ambas versiones mediante número de nodos visitados, soluciones encontradas y tiempo de ejecución.

### Instancias evaluadas
1. Verificación `n=3`
2. Verificación `n=4`
3. Referencia oficial
4. `completa_n8`
5. `completa_n6`
6. `completa_n10`
7. `relajada_n8`
8. `sinrestr_n6`

Las instancias grandes pueden alcanzar los límites de seguridad establecidos y quedar marcadas como parciales.

---

## Experimentación

Los resultados experimentales se almacenan en:

```text
results/
```
Incluyen archivos CSV y gráficas utilizadas para analizar el comportamiento de ambos módulos.

Para generar las gráficas se utilizan los scripts disponibles en:
```text
scripts/
```

---

## Resultados principales

Las pruebas de **Fuerza Bruta** muestran un crecimiento rápido del número de candidatos evaluados al aumentar la longitud de la contraseña.

En la instancia `wpctwv` (A1, n=6) se evaluaron aproximadamente:

```text
268.293.502 candidatos
```
lo que produjo el mayor tiempo de ejecución de las pruebas realizadas.

En **Backtracking**, la versión con poda permitió reducir considerablemente los nodos explorados frente a la versión sin poda, manteniendo las mismas soluciones en las pruebas completas.

---