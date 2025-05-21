#  Grayscale Image Processing Library

A modular and object-oriented C++ library for grayscale image manipulation using the PGM (Portable Gray Map) format. This project implements core image processing operations such as brightness/contrast adjustment, gamma correction, and image convolution using custom-defined kernels.

## Features

* Load and save PGM (ASCII) images
* Region of Interest (ROI) extraction
* Image arithmetic (add, subtract, scale)
* Operator overloading for intuitive image manipulation
* Gamma correction and brightness/contrast adjustment
* Convolution with custom kernels (e.g., Sobel, Gaussian, Mean Blur)

##  Classes Overview

### Core Data Structures

* **Size**: Represents dimensions (width, height) and supports comparison operators based on area.
* **Point**: Represents a 2D point (x, y).
* **Rectangle**: Defines a rectangular region and supports translation, intersection (`&`), and union (`|`).

### Image Class

Encapsulates the grayscale image as a 2D matrix (`unsigned char**`) with full dynamic memory management (Rule of Three).

Key methods:

* `bool load(std::string path)` / `bool save(std::string path)`
* `Image operator+(const Image&)`, `operator-(const Image&)`, `operator*(double)`
* `bool getROI(...)`: Extracts a sub-image
* `unsigned char& at(x, y)` and `row(y)` for pixel-level access
* `static Image zeros(w, h)` / `ones(w, h)` factory methods

### Image Processing Interface

`class ImageProcessing`

* Defines the virtual method: `void process(const Image& src, Image& dst)`
* Subclassed by:

  * **BrightnessContrast**: Applies linear transformation α⋅src + β
  * **GammaCorrection**: Applies gamma curve: `dst = pow(src, gamma)`
  * **Convolution**: Applies a kernel to extract features or blur

##  PGM Format Support

Supports PGM ASCII format (`P2`) for easy debugging and file handling. Allows users to read/write human-readable grayscale images.

##  What I Learned

* Solid grasp of Object-Oriented Programming in C++ (constructors, destructors, polymorphism, operator overloading)
* Dynamic memory management and the Rule of Three
* Working with 2D arrays and file streams
* Implementation of image processing algorithms from scratch
* Interface-based design for algorithm extensibility

##  Example Usage

```cpp
Image img;
img.load("input.pgm");
Image out;
GammaCorrection gamma(0.8);
gamma.process(img, out);
out.save("output.pgm");
```


##  References

* [PGM format spec](https://netpbm.sourceforge.net/doc/pgm.html)
* Computer Vision & Image Processing textbooks

---

