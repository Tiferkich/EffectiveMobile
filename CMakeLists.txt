cmake_minimum_required(VERSION 3.22.1)
project(EffectiveMobile)

set(CMAKE_CXX_STANDARD 20)

add_library(ImageBMP programme-classes/ImageBMP.h programme-classes/ImageBMP.cpp programme-classes/Image.h)


add_executable(EffectiveMobile main.cpp)

target_link_libraries(EffectiveMobile ImageBMP)
