cmake_minimum_required(VERSION 3.14)
project(MandelbrotPythonBinding)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pybind11 REQUIRED)

add_library(mandelbrot MODULE
    bindings.cpp
)

target_include_directories(mandelbrot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(mandelbrot PRIVATE PYBIND11_MODULE_NAME=mandelbrot)

set_target_properties(mandelbrot PROPERTIES
    PREFIX ""
    OUTPUT_NAME "mandelbrot"
    SUFFIX ".so"
)

target_link_libraries(mandelbrot PRIVATE pybind11::module)
