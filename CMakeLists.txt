cmake_minimum_required(VERSION 3.10)
project(mlkem_lib)

set(CMAKE_CXX_STANDARD 17)

# Define the shared library
add_library(mlkem SHARED src/mlkem.cpp)

# Include directory
target_include_directories(mlkem PUBLIC include)

# Set correct output file extensions
if(WIN32)
    set_target_properties(mlkem PROPERTIES SUFFIX ".dll")
else()
    set_target_properties(mlkem PROPERTIES SUFFIX ".so")
endif()
