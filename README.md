# Asteroids clone

## Overview

This is a small clone of the retro game asteroids.

I started making it with the purpose of learning to use SFML, get
comfortable writing C++ code, and managing a 'larger' project.

## Screenshots

![Title_Screen](./title_screen.png)
![Game](./game.png)

## Dependecies

- CMake 3.23
- GCC 11.2 or equivalent

## Build
1. Go to install dir and create build directory
```shell
cd asteroids-clone
mkdir build
```
2. Build using CMake
```shell
cmake .. -G "MinGW Makefiles"
cmake --build . -- -j4 -O
```
3. Run executable
```shell
./asteroids-clone
```

After the project is built, you will just have tu run the executable.