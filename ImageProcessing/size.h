#pragma once
class Size {
protected:
	unsigned int width;
	unsigned int height;
public:
	Size();
	Size(unsigned int w, unsigned int h) : width(w), height(h) {};
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getArea() const;
	bool setWidth(unsigned int w);
	bool setHeight(unsigned int h);
	bool operator==(const Size& other)const;
	bool operator<(const Size& other)const;
	bool operator<=(const Size& other)const;
	bool operator>(const Size& other)const;
	bool operator>=(const Size& other)const;
};