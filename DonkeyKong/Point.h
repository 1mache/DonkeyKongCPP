#pragma once

//class that represents an ordered pair of x,y
class Point {
	int x, y;

public: 
	Point() = default;
	constexpr Point(int _x, int _y): x(_x), y(_y) {}

	Point operator+(const Point& other) const
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
	// same with left/right
	Point oneRight() const { return Point(x + 1, y); }
	Point oneLeft() const { return Point(x - 1, y); }
};
