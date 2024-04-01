#include "point.h"

Point::Point() {
	x = 0;
	y = 0;
};

int Point::getX() const
{
	return x;
};
int Point::getY() const {
	return y;
};
bool Point::setX(int x) {
	this->x = x;
	return this->x == x;
};
bool Point::setY(int y) {
	this->y = y;
	return this->y == y;
};