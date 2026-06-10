cmake_minimum_required(VERSION 3.20)

project(LunarLander LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(LunarLander
    engine.cpp
    GameScene.cpp
    Lander.cpp
    LoadingScene.cpp
    MenuScene.cpp
    SceneManager.cpp
    Terrain.cpp
)

target_link_libraries(LunarLander PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)