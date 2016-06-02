cmake_minimum_required(VERSION 2.8)
project(WithCmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${WithCmake_SOURCE_DIR}/cmake")

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



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES Hexagon_Eventhandler.c Hexagon_GetSpriteNr.c Hexagon_Gravity.c Hexagon_Main.c Hexagon_Movement.c Hexagon_Platform.c meny.c menymusic.c options.c)

add_executable(WithCmake ${SOURCE_FILES} background.bmp ball.bmp blocks.bmp dot.bmp Hexagon_Final.cbp Hexagon_Final.depend
                Hexagon_Final.layout Humansprites.bmp plattform.bmp Hexagon_Environment.h Highscore.png Highscore_Red.png Options.png Options_red.png Start.png Start_Red.png Exit.png Exit_Red.png mario.mp3 Checkbox.png CheckboxCross.png Sound.png)