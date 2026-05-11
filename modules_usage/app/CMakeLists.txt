cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)
target_sources(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../drivers/our_driver/our_driver.c
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

zephyr_syscall_include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
