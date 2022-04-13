@mkdir obj
@mkdir src\lib
@mkdir build
@git clone --branch 2.5.1 https://github.com/SFML/SFML.git
@cmake -G "MinGW Makefiles" -S SFML -B build
@cd build && mingw32-make
