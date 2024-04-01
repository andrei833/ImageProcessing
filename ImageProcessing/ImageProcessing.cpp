#include "ImageProcessing.h"
#include <cmath>
#include <iostream>


void BrightnessContrastAdjustment::process(const Image& src, Image& dst) {
	dst = src;
	const Image ones = Image::ones(dst.width(), dst.height());
	dst = ((src * alpha) + ones * beta);
};

void GammaCorrection::process(const Image& src, Image& dst) {
    dst = src;
    for (int row = 0; row < dst.height(); row++) {
        for (int col = 0; col < dst.width(); col++) {
            double correctedValue = pow(src.at(row, col) / 255.0, 1.0 / gamma) * 255.0;
            correctedValue = std::max(0.0, std::min(255.0, correctedValue));
            dst.at(row, col) = static_cast<unsigned char>(correctedValue);
        }
    }
};

void Convolution::process(const Image& src, Image& dst) {
    dst = src;
    for (int row = 0; row < src.height() ; row++) {
        for (int col = 0; col < src.width() ; col++) {
            double sum = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (row +i >=0 && row+i<=src.height() && col + i >= 0 && col+i <= src.width())
                    sum += src.at(row + i, col + j) * m_kernel[i + 1][j + 1];
                }
            }
            switch (type)
            {
            case Identity:
                dst.at(row, col) = sum;
                break;
            case MeanBlur:
                dst.at(row, col) = sum/9;
                break;
            case GaussianBlur:
                dst.at(row, col) = sum/16;
                break;
            case HorizontalSobel:
                dst.at(row, col) = sum / 8 + 127.5;
                break;
            case VerticalSobel:
                dst.at(row, col) = sum / 8 + 127.5;
                break;
            case Laplacian:
                dst.at(row, col) = sum;
                break;
            default:
                dst.at(row, col) = sum;
                break;
            }
            
        }
    }
}