#pragma once
#include "rectangle.h"
#include <string>
class Image
{
private:
	unsigned char** m_data;
	unsigned int m_width;
	unsigned int m_height;
public:
	Image();
	Image(unsigned int w, unsigned int h);
	~Image();

	Image(const Image& other);
	Image& operator=(const Image& other);
	
	bool load(std::string imagePath);
	bool save(std::string imagePath) const;

	Image operator+(const Image& other);
	Image operator-(const Image& other);
	//Implement the + and -operators for the pixel wise addition and subtraction between two images.
	//	These operations only make sense for images of the same size; if the images have different
	//	resolutions, an exception will be thrown.

	Image operator*(double s) const;

	bool getROI(Image& roiImg, Rectangle roiRect);
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	
	bool isEmpty() const;
	Size size() const;

	unsigned int width() const;
	unsigned int height() const;
	unsigned char& at(unsigned int x, unsigned int y) const;
	unsigned char& at(Point pt) const;
	unsigned char* row(int y);

	//void release();

	//friend std::ostream& operator<<(std::ostream& os, const Image& dt);
	//friend std::istream& operator>>(std::istream& is, Image& dt);

	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);
};