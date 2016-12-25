#pragma once

#include "Board.h"
#include "Location.h"
#include "Snake.h"
#include <random>

class Wall
{
public:
	void Init(int xGrid, int yGrid);
	void Init(std::mt19937& rng, Board& brd, Snake& snek);
	void Draw(Board& brd) const;
	Location GetLocation() const;

private:
	Location loc;
	Color c = Colors::Magenta;
	bool initialized = false;
};