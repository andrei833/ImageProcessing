#pragma once
#include "point.h"
#include "size.h"

class Rectangle : public Point, public Size {
public:
	Rectangle(int x, int y, unsigned int w, unsigned int h) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
	}
	Rectangle() : Point(), Size() {};
	Rectangle operator+(const Point& p) const;
	Rectangle operator-(const Point& p) const;
	Rectangle operator&&(const Rectangle& other) const;
	Rectangle operator||(const Rectangle& other) const;
};