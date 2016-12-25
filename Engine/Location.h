#pragma once

class Location
{
public:
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}
	bool operator==(const Location& other) const
	{
		return x == other.x && y == other.y;
	}

	int x;
	int y;
};