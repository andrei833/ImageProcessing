#include <iostream>
#include <math.h>
#include "rectangle.h"

Rectangle Rectangle::operator+(const Point& p) const {
	return Rectangle(x + p.getX(), y + p.getY(), this->width, this->height);
};
Rectangle Rectangle::operator-(const Point& p) const{
	return Rectangle(x - p.getX(), y - p.getY(), this->width, this->height);
}

Rectangle Rectangle::operator&&(const Rectangle& other) const {
	const Size* thisSize = static_cast<const Size*>(this);
	const Size* otherSize = static_cast<const Size*>(&other);
    unsigned int intersectWidth = 0, intersectHeight = 0;

    if (getX() < other.getX()) {
        intersectWidth = std::max(0, (int)std::min(getX() + getWidth(), other.getX() + other.getWidth()) - other.getX());
    }
    else {
        intersectWidth = std::max(0, (int)std::min(other.getX() + other.getWidth(), getX() + getWidth()) - getX());
    }

    if (getY() < other.getY()) {
        intersectHeight = std::max(0, (int)std::min(getY() + getHeight(), other.getY() + other.getHeight()) - other.getY());
    }
    else {
        intersectHeight = std::max(0, (int)std::min(other.getY() + other.getHeight(), getY() + getHeight()) - getY());
    }

    // Calculate top-left coordinates of the intersection rectangle
    int intersectX = std::max(getX(), other.getX());
    int intersectY = std::max(getY(), other.getY());

    // Create and return the intersection rectangle
    return Rectangle(intersectX, intersectY, intersectWidth, intersectHeight);
};

Rectangle Rectangle::operator||(const Rectangle& other) const {
    int minX = std::min(getX(), other.getX());
    int minY = std::min(getY(), other.getY());
    int maxX = std::max(getX() + getWidth(), other.getX() + other.getWidth());
    int maxY = std::max(getY() + getHeight(), other.getY() + other.getHeight());

    int unionWidth = maxX - minX;
    int unionHeight = maxY - minY;

    return Rectangle(minX, minY, unionWidth, unionHeight);
}