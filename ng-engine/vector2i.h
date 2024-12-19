#pragma once

class Vector2i {
private:
	int _x;
	int _y;
public:
	Vector2i(int x, int y);

	int x() const;
	int y() const;
};