cmake_minimum_required(VERSION 2.8)
project(NAME) # Replace NAME project name in ENTIRE file, 3 places.


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ”${NAME_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)



include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_NET_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_NET_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Remove ALL lines containing SDL2_MIXER_LIBRARIES if not using said library, 3 lines.

set(SOURCE_FILES fileshere.c andhere.h) # .c & .h files here

add_executable(TNAME ${SOURCE_FILES} imageshere.bmp) # Image files here