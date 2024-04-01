#pragma once
#include "Image.h"
#include <iostream>

class ImageProcessing {
public:
    virtual void process(const Image& src, Image& dst) = 0;
};


class BrightnessContrastAdjustment : public ImageProcessing {
private:
    double alpha;
    double beta;

public:
    BrightnessContrastAdjustment() : alpha(1), beta(0) {};
    BrightnessContrastAdjustment(double a, double b) : alpha(a), beta(b) {};
    void process(const Image& src, Image& dst) override;
};


class GammaCorrection : public ImageProcessing {
private:
    double gamma;

public:
    GammaCorrection() : gamma(1) {};
    GammaCorrection(double g) : gamma(g) {};
    void process(const Image& src, Image& dst) override;
};

class Convolution : public ImageProcessing
{
public:
    enum ConvolutionType {
        Identity,
        MeanBlur,
        GaussianBlur,
        HorizontalSobel,
        VerticalSobel,
        Laplacian
    };
private:
    int** m_kernel;
    unsigned int m_kernelWidth;
    unsigned int m_kernelHeight;
    ConvolutionType type;
public:
    Convolution() {
        m_kernelWidth = 3;
        m_kernelHeight = 3;
        m_kernel = new int* [m_kernelHeight];
        for (int i = 0; i < m_kernelHeight; i++)
        {
            m_kernel[i] = new int[m_kernelWidth];
        }
        type = Identity;
        for (int i = 0; i < m_kernelHeight; i++)
        {
            for (int j = 0; i < m_kernelWidth; i++)
            {
                m_kernel[i][j] = 0;
            }
        }
        m_kernel[1][1] = 1;
    };

    Convolution(ConvolutionType convType) {
        m_kernelWidth = 3;
        m_kernelHeight = 3;
        m_kernel = new int* [m_kernelHeight];
        type = convType;
        switch (type)
        {
        case Identity:
            for (unsigned int i = 0; i < m_kernelHeight; i++)
            {
                m_kernel[i] = new int[m_kernelWidth];
            }
            for (unsigned int i = 0; i < m_kernelHeight; i++)
            {
                for (unsigned int j = 0; j < m_kernelWidth; j++)
                {
                    m_kernel[i][j] = 0;
                }
            }
            m_kernel[1][1] = 1;
            break;
        case MeanBlur:
            m_kernel[0] = new int[3] {1, 1, 1};
            m_kernel[1] = new int[3] {1, 1, 1};
            m_kernel[2] = new int[3] {1, 1, 1};
            break;
        case GaussianBlur:
            m_kernel[0] = new int[3] {1, 2, 1};
            m_kernel[1] = new int[3] {2, 4, 2};
            m_kernel[2] = new int[3] {1, 2, 1};
            break;
        case HorizontalSobel:
            m_kernel[0] = new int[3] {-1, -2, -1};
            m_kernel[1] = new int[3] {0, 0, 0};
            m_kernel[2] = new int[3] {1, 2, 1};
            break;
        case VerticalSobel:
            m_kernel[0] = new int[3] {-1, 0, 1};
            m_kernel[1] = new int[3] {-2, 0, 2};
            m_kernel[2] = new int[3] {-1, 0, 1};
            break;
        case Laplacian:
            m_kernel[0] = new int[3] {1, 1, 1};
            m_kernel[1] = new int[3] {1, -8, 1};
            m_kernel[2] = new int[3] {1, 1, 1};
            break;
        default:
            std::cerr << "Unknown convolution type!" << std::endl;
            break;
        }

    };

    ~Convolution() {
        for (int i = 0; i < m_kernelHeight; i++) {
            delete[] m_kernel[i];
        }
        delete[] m_kernel;
    };

    void process(const Image& src, Image& dst) override;
};


class ShapeDrawing : public ImageProcessing {
public:
    void drawCircle(Image& img, Point center, int radius, unsigned char color) {
        int x = radius - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - (radius << 1);

        while (x >= y) {
            img.at(center.getX() + x, center.getY() + y) = color;
            img.at(center.getX() + y, center.getY() + x) = color;
            img.at(center.getX() - y, center.getY() + x) = color;
            img.at(center.getX() - x, center.getY() + y) = color;
            img.at(center.getX() - x, center.getY() - y) = color;
            img.at(center.getX() - y, center.getY() - x) = color;
            img.at(center.getX() + y, center.getY() - x) = color;
            img.at(center.getX() + x, center.getY() - y) = color;

            if (err <= 0) {
                y++;
                err += dy;
                dy += 2;
            }
            if (err > 0) {
                x--;
                dx += 2;
                err += dx - (radius << 1);
            }
        }
    }

    void drawLine(Image& img, Point p1, Point p2, unsigned char color) {
        int x0 = p1.getX();
        int y0 = p1.getY();
        int x1 = p2.getX();
        int y1 = p2.getY();

        int dx = abs(x1 - x0);
        int sx = x0 < x1 ? 1 : -1;
        int dy = -abs(y1 - y0);
        int sy = y0 < y1 ? 1 : -1;
        int err = dx + dy;
        int e2;

        while (true) {
            img.at(x0, y0) = color;
            if (x0 == x1 && y0 == y1) break;
            e2 = 2 * err;
            if (e2 >= dy) {
                err += dy;
                x0 += sx;
            }
            if (e2 <= dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

    void drawRectangle(Image& img, Rectangle r, unsigned char color) {
        int x = r.getX();
        int y = r.getY();
        int width = r.getWidth();
        int height = r.getHeight();

        for (int i = x; i < x + width; ++i) {
            img.at(i, y) = color;
            img.at(i, y + height - 1) = color;
        }

        for (int i = y; i < y + height; ++i) {
            img.at(x, i) = color;
            img.at(x + width - 1, i) = color;
        }
    }

    void drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
        int minX = std::min(tl.getX(), br.getX());
        int minY = std::min(tl.getY(), br.getY());
        int maxX = std::max(tl.getX(), br.getX());
        int maxY = std::max(tl.getY(), br.getY());

        Rectangle rect(minX, minY, maxX - minX + 1, maxY - minY + 1);
        drawRectangle(img, rect, color);
    }

    void process(const Image& src, Image& dst) override {
        // This is a virtual function required by the base class
        // We don't need to implement it for this class, as we are not processing images
        // Instead, we are providing drawing functionalities directly
    }
};