cmake_minimum_required(VERSION 3.28)
project(yugioh_master_duel_kit)

set(CMAKE_CXX_STANDARD 26)

add_executable(yugioh_master_duel_kit src/main.cpp
        src/service.h
        src/service.cpp)
