#pragma once

class Point {
	int x, y;

public: 
	constexpr Point(int _x, int _y): x(_x), y(_y) {}

	Point operator+(const Point& other)
	{
		return Point(x + other.x, y + other.y);
	}

	bool operator==(const Point& other) const
	{
		return (x == other.x) && (y == other.y);
	}

	int getX() const { return x; }
	int getY() const { return y; }

	//return position that is 1 above/below this position
	Point oneAbove() const { return Point(x, y - 1); }
	Point oneBelow () const { return Point(x, y + 1); }
};
