cmake_minimum_required(VERSION 3.15)
project(wepdemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(wepdemo main.cpp bitmap_image.hpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event
        COMMAND ${CMAKE_COMMAND} -E copy_directory #-E copy_if_different  # which executes "cmake - E copy_if_different..."
        ${CMAKE_SOURCE_DIR}/resources      # <--this is in-file
        ${CMAKE_CURRENT_BINARY_DIR}) # <--this is out-file path