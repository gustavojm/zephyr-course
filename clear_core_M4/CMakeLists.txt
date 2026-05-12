cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED)
project(clear_M4)

target_sources(app PRIVATE src/main.cpp)
