#pragma once

#include <complex>
#include <vector>
#include <mutex>

class MandelbrotGenerator
{
public:
    using Complex = std::complex<double>;

    struct Pixel
    {
        unsigned int x;
        unsigned int y;
        double value;
    };

    explicit MandelbrotGenerator(unsigned int width, unsigned int height)
        : width_(width), height_(height), pixels_(width * height, {0, 0, 0.0}) {}

    void setZoom(double zoom) { zoom_ = zoom; }
    void setCenter(double real, double imag) { center_ = Complex(real, imag); }
    void setMaxIterations(unsigned int iter) { maxIterations_ = iter; }

    void computeRegion(unsigned int y_start, unsigned int y_end)
    {
        double scale = 1.0 / zoom_;
        for (unsigned int y = y_start; y < y_end; ++y)
        {
            for (unsigned int x = 0; x < width_; ++x)
            {
                double real = (x - width_ / 2.0) * scale / width_ + center_.real();
                double imag = (y - height_ / 2.0) * scale / height_ + center_.imag();
                double val = mandelbrot(real, imag);

                Pixel px{x, y, val};
                pixels_[y * width_ + x] = px;
            }
        }
    }

    const std::vector<Pixel> &getPixels() const { return pixels_; }
    unsigned int getWidth() const { return width_; }
    unsigned int getHeight() const { return height_; }

private:
    unsigned int width_;
    unsigned int height_;
    double zoom_ = 1.0;
    Complex center_ = {0.0, 0.0};
    unsigned int maxIterations_ = 500;
    std::vector<Pixel> pixels_;

    double mandelbrot(double real, double imag) const
    {
        Complex c(real, imag);
        Complex z(0.0, 0.0);
        unsigned int i = 0;
        while (std::abs(z) <= 2.0 && i < maxIterations_)
        {
            z = z * z + c;
            ++i;
        }

        if (i == maxIterations_)
            return static_cast<double>(i);

        double log_zn = std::log(z.real() * z.real() + z.imag() * z.imag()) / 2.0;
        double nu = std::log(log_zn / std::log(2)) / std::log(2);
        return i + 1 - nu;
    }
};
