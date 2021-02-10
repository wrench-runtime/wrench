cmake_minimum_required(VERSION 3.6)
project(wrench_all)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# use -DWRENCH_STATIC_MODULES=a;b;c to include binary modules in wrench
set(WRENCH_STATIC_MODULES "" CACHE STRING "Wrench native modules to statically link against the executable")
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/static_plugins.in)
set(static_modules "")

if(DEFINED WRENCH_STATIC_MODULES)
message(STATUS "Building static modules: ${WRENCH_STATIC_MODULES}")
foreach(module_name IN LISTS WRENCH_STATIC_MODULES)
    list(APPEND static_modules "module_${module_name}_static")
    file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/include/static_plugins.in "REGISTER_PLUGIN(${module_name});\n")
  endforeach()
endif()


# The main program
add_executable(wrench src/wrench.c include/static_plugins.in)
target_include_directories(wrench PRIVATE include)
target_link_libraries(wrench PRIVATE wren_runtime readfile ${static_modules})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_subdirectory(runtime)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wren/main.wren ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main.wren COPYONLY)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/wren_modules)
add_subdirectory(module-buffer)
add_subdirectory(module-sdl)