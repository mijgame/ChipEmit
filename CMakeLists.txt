cmake_minimum_required(VERSION 3.15)
project(ChipEmit)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChipEmit main.cpp libraries/pugixml-1.10/pugixml.cpp parsing/register.hpp parsing/peripheral.hpp parsing/access_level.hpp parsing/field.hpp parsing/device.hpp emitting/cpp_emitter.hpp)
target_include_directories(ChipEmit PUBLIC libraries/pugixml-1.10)