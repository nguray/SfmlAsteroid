cmake_minimum_required(VERSION 3.5)

project(sfmlAsteroid VERSION 0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCES
        main.cpp
        Rock.h Rock.cpp
        Bullet.h Bullet.cpp
        MySprite.h MySprite.cpp
        RVector2D.h RVector2D.cpp
)

add_executable(sfmlAsteroid ${PROJECT_SOURCES})

set(SFML_STATIC_LIBRARIES FALSE)

include(CheckIncludeFileCXX)
check_include_file_cxx("format" CXX_FORMAT_SUPPORT)
if (NOT CXX_FORMAT_SUPPORT)
    find_package(fmt REQUIRED)
endif()

if (NOT CXX_FORMAT_SUPPORT)
    target_link_libraries(${PROJECT_NAME} fmt::fmt)
endif()

find_package(SFML REQUIRED COMPONENTS window graphics system audio)

target_compile_features(sfmlAsteroid PUBLIC cxx_std_20)
target_compile_definitions(sfmlAsteroid PRIVATE SFML_SHARED)

target_link_libraries(sfmlAsteroid sfml-graphics sfml-window sfml-audio sfml-system)
