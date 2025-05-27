CXX := g++
CXXFLAGS := -O3 -Wall -shared -std=c++17 -fPIC

PYTHON_VERSION  := $(shell python3 -c "import sys; print(f'{sys.version_info[0]}.{sys.version_info[1]}')")
PYTHON_INCLUDE  := $(shell python3 -c "from sysconfig import get_paths as gp; print(gp()['include'])")
PYTHON_LIBDIR   := $(shell python3 -c "from sysconfig import get_paths as gp; print(gp()['platlib'])")

SRC := bindings.cpp
HDR := mandelbrot.hpp
OUT := mandelbrot.so

PYBIND11_INCLUDES := $(shell python3 -m pybind11 --includes)

$(OUT): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(PYBIND11_INCLUDES) -I$(PYTHON_INCLUDE) $(SRC) -o $(OUT)

.PHONY: clean
clean:
	rm -f $(OUT)
