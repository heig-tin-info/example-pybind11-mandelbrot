#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "mandelbrot.hpp"

namespace py = pybind11;

PYBIND11_MODULE(mandelbrot, m)
{
    py::class_<MandelbrotGenerator::Pixel>(m, "Pixel")
        .def_readonly("x", &MandelbrotGenerator::Pixel::x)
        .def_readonly("y", &MandelbrotGenerator::Pixel::y)
        .def_readonly("value", &MandelbrotGenerator::Pixel::value);

    py::class_<MandelbrotGenerator>(m, "MandelbrotGenerator")
        .def(py::init<unsigned int, unsigned int>())
        .def("setZoom", &MandelbrotGenerator::setZoom)
        .def("setCenter", &MandelbrotGenerator::setCenter)
        .def("setMaxIterations", &MandelbrotGenerator::setMaxIterations)
        .def("computeRegion", &MandelbrotGenerator::computeRegion)

        .def("getPixels", &MandelbrotGenerator::getPixels)
        .def("getWidth", &MandelbrotGenerator::getWidth)
        .def("getHeight", &MandelbrotGenerator::getHeight);
}
