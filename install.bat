@move build\lib\*.a src\lib
@move build\lib\*.dll .
@move SFML\include\SFML src/include
@move SFML\extlibs\bin\x64\openal32.dll .
@rd /s /q build
@rd /s /q SFML