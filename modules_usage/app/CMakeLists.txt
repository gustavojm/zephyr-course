cmake_minimum_required(VERSION 3.20.0)

get_filename_component(MODULES_USAGE_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

list(APPEND ZEPHYR_EXTRA_MODULES
    ${MODULES_USAGE_ROOT}
)

find_package(Zephyr REQUIRED)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)
