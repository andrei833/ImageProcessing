#pragma once
class Point {
protected:
	int x;
	int y;
public:
	Point();
	Point(int x1, int y1) : x(x1), y(y1) {};
	int getX() const;
	int getY() const;
	bool setX(int x);
	bool setY(int y);
	
};