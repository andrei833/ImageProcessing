#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
#include <algorithm>
#include "rectangle.h"
#include "image.h"
#include "imageProcessing.h"

void testIntersection() {
    Rectangle rect1(0, 0, 24, 10);
    Rectangle rect2(3, 2, 12, 3);
    Rectangle intersection = rect1 && rect2;

    std::cout << "Rectangle 1: (" << rect1.getX() << ", " << rect1.getY() << ", " << rect1.getWidth() << ", " << rect1.getHeight() << ")" << std::endl;
    std::cout << "Rectangle 2: (" << rect2.getX() << ", " << rect2.getY() << ", " << rect2.getWidth() << ", " << rect2.getHeight() << ")" << std::endl;

    std::cout << "Intersection Rectangle: ";
    if (intersection.getWidth() == 0 || intersection.getHeight() == 0) {
        std::cout << "No intersection" << std::endl;
    }
    else {
        std::cout << "(" << intersection.getX() << ", " << intersection.getY() << ", " << intersection.getWidth() << ", " << intersection.getHeight() << ")" << std::endl;
    }
    std::cout << std::endl;
}


void test_constructor_with_dimensions() {
    unsigned int width = 10;
    unsigned int height = 5;
    Image img(width, height);
}

void test_copy_constructor() {
    unsigned int width = 10;
    unsigned int height = 5;
    Image original(width, height);


    Image copy(original);
}

void test_copy_assignment_operator() {
    unsigned int width = 10;
    unsigned int height = 5;
    Image original(width, height);
    Image copy = original;
}

void test_image_sum_load_save() {
    Image i1;
    Image i2;
    std::string imagePath = "G:\\OOP\\ImageProcessing\\ImageProcessing\\casablanca.ascii.pgm";
    if (!i1.load(imagePath)) {
        std::cerr << "Failed to load image from path: " << imagePath << std::endl;
        return;
    }
    if (!i2.load(imagePath)) {
        std::cerr << "Failed to load image from path: " << imagePath << std::endl;
        return;
    }

    Image i3 = i1 + i2;
    std::string outputPath = "G:\\OOP\\ImageProcessing\\ImageProcessing\\output.pgm";
    if (!i3.save(outputPath)) {
        std::cerr << "Failed to save image to path: " << outputPath << std::endl;
        return;
    }

    std::cout << "Image loaded, summed, and saved successfully." << std::endl;
}

void test_roi() {
    // Load an image from file
    Image originalImage;
    if (!originalImage.load("G:\\OOP\\ImageProcessing\\ImageProcessing\\casablanca.ascii.pgm")) {
        std::cerr << "Failed to load the image." << std::endl;
    }

    // Define a rectangle for the ROI
    Rectangle roiRect(1, 1, 255, 255); // Example: ROI starting from (1,1) with width=2 and height=2

    // Create an image to store the ROI
    Image roiImage;

    // Get the ROI
    if (!originalImage.getROI(roiImage, roiRect)) {
    }

    std::string outputPath = "G:\\OOP\\ImageProcessing\\ImageProcessing\\output.pgm";
    roiImage.save(outputPath);
}

void testBright() {
    Image source;
    Image result;
    source.load("G:\\OOP\\ImageProcessing\\ImageProcessing\\casablanca.ascii.pgm");
    BrightnessContrastAdjustment setting1(1,+120);
    setting1.process(source,result);
    result.save("G:\\OOP\\ImageProcessing\\ImageProcessing\\output.pgm");
}

void testGammaCorrection() {
    Image source;
    Image result;

    // Load the source image
    source.load("G:\\OOP\\ImageProcessing\\ImageProcessing\\casablanca.ascii.pgm"); // load leaks

    // Create a GammaCorrection object with a gamma value of 1.5
    GammaCorrection gammaCorrection(0.2);

    // Apply gamma correction to the source image
    gammaCorrection.process(source, result);

    // Save the result to an output file
    result.save("G:\\OOP\\ImageProcessing\\ImageProcessing\\output_gamma_corrected.pgm");
}

void testConvolution() {
    Image source;
    Image result;

    // Load the source image
    source.load("G:\\OOP\\ImageProcessing\\ImageProcessing\\hands.ascii.pgm"); // load leaks

    // Create a GammaCorrection object with a gamma value of 1.5
    Convolution identity(Convolution::ConvolutionType::MeanBlur);

    // Apply gamma correction to the source image
    identity.process(source, result);

    // Save the result to an output file
    result.save("G:\\OOP\\ImageProcessing\\ImageProcessing\\output_convolution.pgm");
}

void testDraw() {
    Image img;
    img.load("G:\\OOP\\ImageProcessing\\ImageProcessing\\hands.ascii.pgm");

    ShapeDrawing drawer;
    Point center(50, 50);
    int radius = 20;
    unsigned char color = 255;

    drawer.drawCircle(img, center, radius, color);

    Point p1(10, 20);
    Point p2(30, 40);

    drawer.drawLine(img, p1, p2, color);

    Point tl(5, 5);
    Point br(55, 45);
    drawer.drawRectangle(img, tl, br, color);

    img.save("G:\\OOP\\ImageProcessing\\ImageProcessing\\draw.pgm");
}

int main() {
    //test_constructor_with_dimensions();
    //test_copy_constructor();
    //test_copy_assignment_operator();
    //testIntersection();
    //test_roi();
    //test_image_sum_load_save();
    //testBright();
    //testGammaCorrection();
    //testConvolution();
    testDraw();
    _CrtDumpMemoryLeaks();
    return 0;
}
