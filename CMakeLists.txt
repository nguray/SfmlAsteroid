cmake_minimum_required(VERSION 3.25)

project(sfmlAsteroid VERSION 0.1 LANGUAGES CXX)

add_executable(sfmlAsteroid main.cpp)

set(SFML_STATIC_LIBRARIES FALSE)

find_package(SFML COMPONENTS window graphics system audio)

target_compile_features(sfmlAsteroid PUBLIC cxx_std_17)
target_compile_definitions(sfmlAsteroid PRIVATE SFML_SHARED)

target_link_libraries(sfmlAsteroid sfml-graphics sfml-window sfml-audio sfml-system)
