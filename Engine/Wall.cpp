#include "Wall.h"
#include "Board.h"
#include "Snake.h"
#include <random>
#include <assert.h>

void Wall::Init(int xGrid, int yGrid)
{
	assert(!initialized);

	loc = { xGrid, yGrid };

	initialized = true;
}

void Wall::Init(std::mt19937 & rng, Board & brd, Snake & snek)
{
	assert(!initialized);

	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc = { xDist(rng), yDist(rng) };
	} while (snek.IsinTile(newLoc));

	loc = newLoc;

	initialized = true;
}

void Wall::Draw(Board & brd) const
{
	assert(initialized);
	brd.DrawCell(loc, c);
}

Location Wall::GetLocation() const
{
	return loc;
}

