#include "size.h"

Size::Size() {
	width = 0;
	height = 0;
}
unsigned int Size::getWidth() const {
	return width;
}
unsigned int Size::getHeight() const {
	return height;
}

unsigned int Size::getArea()const {
	return width * height;
};

bool Size::setWidth(unsigned int w) {
	width = w;
	return width == w;
}
bool Size::setHeight(unsigned int h) {
	height = h;
	return height == h;
};

bool Size::operator==(const Size& other)const {
	return this->getArea() == other.getArea();
};

bool Size::operator<(const Size& other)const {
	return this->getArea() < other.getArea();
};

bool Size::operator<=(const Size& other)const {
	return this->getArea() <= other.getArea();
};

bool Size::operator>(const Size& other)const {
	return this->getArea() > other.getArea();
};

bool Size::operator>=(const Size& other)const {
	return this->getArea() >= other.getArea();
};