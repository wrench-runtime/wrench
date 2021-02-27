cmake_minimum_required(VERSION 3.6)
project(wrench_all)

include(cmake/bin2h.cmake)

#set(CMAKE_FIND_DEBUG_MODE true)

# Allow for targets to define a wren script
define_property(TARGET PROPERTY WREN_SCRIPT BRIEF_DOCS "Wren Script for target" FULL_DOCS "x")

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# use -DWRENCH_STATIC_MODULES=a;b;c to include binary modules in wrench
set(WRENCH_STATIC_MODULES "" CACHE STRING "Wrench native modules to statically link against the executable")
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/static_plugins.in)
set(static_modules "")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(thirdparty/argparse)

# The main program
add_executable(wrench src/wrench.c include/static_plugins.in)
target_include_directories(wrench PRIVATE include thirdparty/argparse)
target_link_libraries(wrench PRIVATE wren_runtime readfile argparse ${static_modules})
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wren/main.wren ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main.wren COPYONLY)
# Runtime directory
add_subdirectory(runtime)

add_executable(test src/test.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/wren_modules)
add_subdirectory(modules)

if(DEFINED WRENCH_STATIC_MODULES)
message(STATUS "Building static modules: ${WRENCH_STATIC_MODULES}")
foreach(module_name IN LISTS WRENCH_STATIC_MODULES)
    list(APPEND static_modules "module_${module_name}_static")
    file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/include/static_plugins.in "REGISTER_PLUGIN(${module_name});\n")
  endforeach()
endif()

# foreach(target_name IN LISTS static_modules)
#   get_target_property(${target_name}_script ${target_name} WREN_SCRIPT)
#   message(STATUS "Scriptfile ${${target_name}_script}")
#   bin2h(SOURCE_FILE "${${target_name}_script}" HEADER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/${target_name}.in VARIABLE_NAME ${target_name})
# endforeach()

