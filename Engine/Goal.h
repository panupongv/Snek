#pragma once

#include "Snake.h"
#include "Board.h"
#include "Wall.h"
#include <random>
class Goal
{
public:
	Goal(std::mt19937& rng, Board& brd, const Snake& snek, const Wall walls[], int wallSize);
	void Respawn(std::mt19937& rng, Board& brd, const Snake& snek, const Wall walls[], int wallSize);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Red;
	Location loc;
};