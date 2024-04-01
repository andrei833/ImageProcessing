#include "image.h"
#include <iostream>
#include <fstream>


Image::Image() {
	m_data = nullptr;
	m_width = 0;
	m_height = 0;
};

Image::Image(unsigned int w, unsigned int h) {
	m_width = w;
	m_height = h;
	m_data = new unsigned char* [h];
	for (unsigned int i = 0; i < h; ++i) {
		m_data[i] = new unsigned char[w];
		for (unsigned int j = 0; j < w; ++j) {
			m_data[i][j] = 0;
		}
	}
}

Image::~Image() {
	if (m_data != nullptr) {
		for (unsigned int i = 0; i < m_height; ++i) {
			delete[] m_data[i];
		}
		delete[] m_data;
	}
}

Image::Image(const Image& other) {
	this->m_width = other.m_width;
	this->m_height = other.m_height;
	m_data = new unsigned char* [m_height];
	for (int i = 0; i < m_height; i++) {
		m_data[i] = new unsigned char[m_width];
	}
	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_width; j++)
			m_data[i][j] = other.m_data[i][j];
};

Image& Image::operator=(const Image& other) {
	if (this != &other) {
		for (int i = 0; i < m_height; i++) {
			delete[] m_data[i];
		}
		delete[] m_data;

		m_width = other.m_width;
		m_height = other.m_height;
		
		m_data = new unsigned char* [m_height];
		for (int i = 0; i < m_height; i++) {
			m_data[i] = new unsigned char[m_width];
		}
		for (int i = 0; i < m_height; i++)
			for (int j = 0; j < m_width; j++)
				m_data[i][j] = other.m_data[i][j];
	}
	return *this;
}

bool Image::load(std::string imagePath) {
	std::ifstream my_file(imagePath);
	if (!my_file.is_open()) {
		std::cerr << "Error: Unable to open file: " << imagePath << std::endl;
		return false;
	}

	std::string format;
	int max_gray_value;

	my_file >> format;
	if (format != "P2") {
		std::cerr << "Error: Unsupported image format: " << format << std::endl;
		return false;
	}

	std::getline(my_file, format);
	std::getline(my_file, format);

	my_file >> m_width >> m_height;
	my_file >> max_gray_value;


	m_data = new unsigned char* [m_height];
	for (unsigned int i = 0; i < m_height; ++i) {
		m_data[i] = new unsigned char[m_width];
	}

	for (unsigned int i = 0; i < m_height; ++i) {
		for (unsigned int j = 0; j < m_width; ++j) {
			int pixel_value;
			my_file >> pixel_value;
			m_data[i][j] = static_cast<unsigned char>(pixel_value);
		}
	}

	return true;
}

bool Image::save(std::string imagePath) const {
	std::ofstream my_file(imagePath);
	if (!my_file) {
		std::cerr << "Error: Unable to create file: " << imagePath << std::endl;
		return false;
	}

	my_file << "P2" << std::endl;
	my_file << "# Simple pgm image example" << std::endl;

	my_file << m_width << " " << m_height << std::endl;

	my_file << "255" << std::endl;

	for (unsigned int i = 0; i < m_height; ++i) {
		for (unsigned int j = 0; j < m_width; ++j) {
			my_file << static_cast<int>(m_data[i][j]) << " ";
		}
		my_file << std::endl;
	}

	return true;
}


Image Image::operator+(const Image& other) {
	Size tSize = this->size();
	Size iSize = other.size();
	if (!(tSize == iSize))
		throw ("The images have different sizes.");

	Image newImage(m_width, m_height);
	for (unsigned int i = 0; i < m_height; ++i) {
		for (unsigned int j = 0; j < m_width; ++j) {
			int sum = static_cast<int>(this->m_data[i][j]) + static_cast<int>(other.m_data[i][j]);
			newImage.m_data[i][j] = static_cast<unsigned char>(std::min(sum,254));
		}
	}
	return newImage;
};

Image Image::operator-(const Image& other) {
	Size tSize = this->size();
	Size iSize = other.size();
	if (!(tSize == iSize))
		throw ("The images have different sizes.");

	Image newImage(m_width, m_height);
	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_width; j++)
			newImage.m_data[i][j] = std::max(this->m_data[i][j] - other.m_data[i][j], 0);
	return newImage;
};

Image Image::operator*(double s) const{
	Image newImage(m_width, m_height);
	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_width; j++)
		{
			int prod = this->m_data[i][j] * s;
			if (prod < 0)
			{
				newImage.m_data[i][j] = 0;
			}
			else if (prod > 254)
			{
				newImage.m_data[i][j] = 254;
			}
			else newImage.m_data[i][j] = this->m_data[i][j] * s;
			
		}
			
	return newImage;
};

bool Image::getROI(Image& roiImg, Rectangle roiRect) {
	int roiWidth = std::min(roiRect.getWidth(), this->m_width - roiRect.getX());
	int roiHeight = std::min(roiRect.getHeight(), this->m_height - roiRect.getY());

	if (roiWidth <= 0 || roiHeight <= 0) {
		std::cerr << "Error: Invalid ROI dimensions." << std::endl;
		return false;
	}

	roiImg.m_width = roiWidth;
	roiImg.m_height = roiHeight;
	roiImg.m_data = new unsigned char* [roiHeight];
	for (int i = 0; i < roiHeight; ++i) {
		roiImg.m_data[i] = new unsigned char[roiWidth];
	}

	for (int i = 0; i < roiHeight; ++i) {
		for (int j = 0; j < roiWidth; ++j) {
			int x = roiRect.getX() + j;
			int y = roiRect.getY() + i;
			roiImg.m_data[i][j] = this->m_data[y][x];
		}
	}

	return true;
}
bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if (x >= m_width || y >= m_height || width == 0 || height == 0) {
		std::cerr << "Error: Invalid ROI dimensions or position." << std::endl;
		return false;
	}

	unsigned int roiWidth = std::min(width, m_width - x);
	unsigned int roiHeight = std::min(height, m_height - y);

	roiImg.m_width = roiWidth;
	roiImg.m_height = roiHeight;
	roiImg.m_data = new unsigned char* [roiHeight];
	for (unsigned int i = 0; i < roiHeight; ++i) {
		roiImg.m_data[i] = new unsigned char[roiWidth];
	}

	for (unsigned int i = 0; i < roiHeight; ++i) {
		for (unsigned int j = 0; j < roiWidth; ++j) {
			roiImg.m_data[i][j] = m_data[y + i][x + j];
		}
	}

	return true;
}


bool Image::isEmpty() const {
	return m_data == nullptr && m_width == 0 && m_height == 0;
};

Size Image::size() const {
	return Size(m_width, m_height);
};

unsigned int Image::width() const {
	return m_width;
};

unsigned int Image::height() const {
	return m_height;
};


unsigned char& Image::at(unsigned int x, unsigned int y) const {
	if (x >= 0 && x < m_height && y >= 0 && y < m_width)
			return m_data[x][y];
	return m_data[0][0];
};

unsigned char& Image::at(Point pt) const{
	int x = pt.getX();
	int y = pt.getY();
	if (x >= 0 && x < m_height && y >= 0 && y < m_width)
		return m_data[x][y];
	throw ("Invalid Point in image.");
};
unsigned char* Image::row(int y) {
	if (y >= 0 && y < m_height)
		return m_data[y];
	return nullptr;
};

Image Image::zeros(unsigned int width, unsigned int height) {
	Image result(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			result.m_data[i][j] = 0;
	return result;
};

Image Image::ones(unsigned int width, unsigned int height) {
	Image result(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			result.m_data[i][j] = 1;
	return result;
};