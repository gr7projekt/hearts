cmake_minimum_required(VERSION 2.8)
project(Gameklient)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Gameklient_SOURCE_DIR}/cmake")

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

set(SOURCE_FILES
    advertisment.png
        aktiv_spelare.png
    Button.c
    button.h
    buttonStruct.h
    CARD.png
    cardPosition.c
    cardPosition.h
    cardStruct.h
    dropzone.png
        game.c
        game.h
    help.png
    includes.h
    libraries.h
    loadCard.c
    loadCard.h
    loadMedia.c
    loadMedia.h
    logik.c
    logik.h
        mainClient.c
    moveCard.c
    moveCard.h
    openWeb.c
    openWeb.h
    position.c
    position.h
        rendering.c
        rendering.h
        recieve.c
        recieve.h
    resetTurn.c
    resetTurn.h
    resolution.h

    send.c
    send.h
    window.c
    window.h)

add_executable(Gameklient ${SOURCE_FILES})