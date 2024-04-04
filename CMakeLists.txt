
cmake_minimum_required(VERSION 3.23)

project(asteroids-clone)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/sfml)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(${CMAKE_SOURCE_DIR}/external/sfml/include)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/src/include/*.h)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_definitions(${PROJECT_NAME} PRIVATE "INSTALL_DIR=\"${CMAKE_SOURCE_DIR}\"")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/sfml/lib/sfml-audio-2.dll ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/sfml/lib/sfml-graphics-2.dll ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/sfml/lib/sfml-network-2.dll ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/sfml/lib/sfml-system-2.dll ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/sfml/lib/sfml-window-2.dll ${CMAKE_BINARY_DIR}
)

        
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/external/sfml/extlibs/bin/x64/openal32.dll ${CMAKE_BINARY_DIR}
)