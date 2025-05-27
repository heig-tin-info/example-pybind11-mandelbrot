import numpy as np
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use("Qt5Agg")

from mandelbrot import MandelbrotGenerator


WIDTH = HEIGHT = 500
ITER = 500
ZOOM = 1.0
CENTER = (-0.75, 0.0)
F, Z = 0.05, 0.22


def pixels_to_rgb(pixels, height, width):
    vals = np.fromiter(
        (p.value for p in pixels), dtype=np.float64, count=height * width
    ).reshape(height, width)

    scale = (1.0 / ZOOM) ** Z
    phases = np.array([4.0, 3.5, 3.0])
    bgr = (0.5 + 0.5 * np.cos(scale * vals[..., None] * F + phases)) * 255
    rgb = bgr.astype(np.uint8)[..., ::-1]  # RGB
    rgb[vals >= ITER] = 0
    return rgb


def main():
    print("Calcul en cours...")
    mandel = MandelbrotGenerator(WIDTH, HEIGHT)
    mandel.setZoom(ZOOM)
    mandel.setCenter(*CENTER)
    mandel.setMaxIterations(ITER)
    mandel.computeRegion(0, HEIGHT)

    print("Conversion image...")
    pixels = mandel.getPixels()
    rgb_image = pixels_to_rgb(pixels, HEIGHT, WIDTH)

    print("Affichage...")
    plt.figure(figsize=(WIDTH / 100, HEIGHT / 100), dpi=100)
    plt.imshow(rgb_image)
    plt.axis("off")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
