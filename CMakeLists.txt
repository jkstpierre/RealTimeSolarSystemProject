# RealTimeSolarSystemProject
# CMakeLists.txt

# Version
cmake_minimum_required (VERSION 3.5)

# Project
project (rtssp)

# Properties
set (CMAKE_C_STANDARD 11)  # Target C11
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   # Output binary to a bin folder
set (CMAKE_C_FLAGS "-Wall -Wextra")     # Show all warnings
set (CMAKE_C_FLAGS_DEBUG "-g -pg")      # Allow for debugging
set (CMAKE_C_FLAGS_RELEASE "-O3")       # Release mode compiler optimizations
set (CMAKE_FIND_LIBRARY_PREFIXES lib)   # Target static libraries
set (CMAKE_FIND_LIBRARY_SUFFIXES a)     # Target static libraries

# Compilation and executable creation
file (GLOB_RECURSE src "src/*.c")
add_executable(rtssp ${src})

# Include directories
target_include_directories (rtssp PRIVATE "./include")
target_include_directories (rtssp PRIVATE ${GLM_INCLUDE_DIRS})

# Packages
## Find and link glfw
find_package(glfw3 REQUIRED)
target_link_libraries(rtssp glfw)