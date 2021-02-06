cmake_minimum_required(VERSION 3.6)
project(wrench_all)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#message(STATUS "C flags, Debug configuration: ${CMAKE_C_FLAGS_DEBUG}")
#message(STATUS "C flags, Release configuration: ${CMAKE_C_FLAGS_RELEASE}")
#message(STATUS "C flags, Release configuration with Debug info: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
#message(STATUS "C flags, minimal Release configuration: ${CMAKE_C_FLAGS_MINSIZEREL}")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_subdirectory(runtime)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wren/main.wren ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main.wren COPYONLY)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/wren_modules)
add_subdirectory(buffer)

