# Asteroids clone

## Overview

This is a small clone of the retro game asteroids.

I started making it with the purpose of learning to use SFML, and get
comfortable writing C++ code.

## Dependecies

- SFML

## Building

The project includes the makefile needed to build it, on a 
windows machine you'll need to install mingw, and on linux you should 
have g++ installed.

You will have to build the SFML binaries, you can do so by following the 
![tutorial](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php) that is found on their website.

You will have to place the **.a** files in a directory lib in '/src/include',
and the **.dll** files in the main dir.

Then to build it you will have to run the command: 

### Windows
'''
cd Asteroids
mingw32-make
'''

### Linux
'''
cd Asteroids
make
'''

## Contributions

At the moment this is just a place to shere this project
with people that want to explore a C++ SFML Example,
and there would be no contributions accepted.

If you find a but you could post an issui about it,
and I will try to fix it.

Feel free to pull this project and use it as you wish.