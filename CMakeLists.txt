cmake_minimum_required(VERSION 3.25)

project(sfmlAsteroid VERSION 0.1 LANGUAGES CXX)

set(PROJECT_SOURCES
        main.cpp
        Bullet.h Bullet.cpp
        MySprite.h MySprite.cpp
)

add_executable(sfmlAsteroid ${PROJECT_SOURCES})

set(SFML_STATIC_LIBRARIES FALSE)

find_package(SFML REQUIRED COMPONENTS window graphics system audio)

target_compile_features(sfmlAsteroid PUBLIC cxx_std_17)
target_compile_definitions(sfmlAsteroid PRIVATE SFML_SHARED)

target_link_libraries(sfmlAsteroid sfml-graphics sfml-window sfml-audio sfml-system)
