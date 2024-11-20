cmake_minimum_required(VERSION 3.16)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(spacedanger VERSION 0.1 LANGUAGES C)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(spacedanger
    src/main.c
    src/app.h
    src/app.c
)

find_package(SDL2 REQUIRED)

target_include_directories(spacedanger
    PUBLIC
        ${SDL2_INCLUDE_DIR}    
)

target_link_directories(spacedanger
    PUBLIC
        ${SDL2_LIBRARY}
)

target_link_libraries(spacedanger
    SDL2
)