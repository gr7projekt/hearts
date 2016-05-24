cmake_minimum_required(VERSION 3.5)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    account.c
    account.h
    card.h
    encrypt.c
    encrypt.h
    gameserver.c
        InetS3.c
    nextplayer.c
    players.c
    players.h
    port_hearts.c
    port_hearts.h
        game.c
        game.h)

add_executable(server ${SOURCE_FILES})