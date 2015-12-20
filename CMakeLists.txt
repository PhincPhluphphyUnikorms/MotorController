cmake_minimum_required(VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME PID)
project(${PROJECT_NAME})

file(GLOB_RECURSE YOUR_HEADERS *.h)

set(${CMAKE_PROJECT_NAME}_SKETCH PID.ino)
generate_arduino_firmware(${CMAKE_PROJECT_NAME})
