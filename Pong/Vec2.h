#pragma once
class Vec2
{
public:
	int x;
	int y;

	Vec2 operator * (Vec2 & rhs) {
		return {x * rhs.x, y * rhs.y};
	}
};

