#include "Goal.h"
#include "Board.h"

Goal::Goal(std::mt19937 & rng, Board & brd, const Snake & snek, const Wall walls[], int wallSize)
{
	Respawn(rng, brd, snek, walls, wallSize);
}

void Goal::Respawn(std::mt19937 & rng, Board & brd, const Snake & snek, const Wall walls[], int wallSize)
{
	std::uniform_int_distribution<int> xDist(1, brd.GetGridWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, brd.GetGridHeight() - 2);

	Location newLoc;

	bool inWall;
	do
	{
		inWall = false;
		newLoc = { xDist(rng), yDist(rng) };
		for (int i = 0; i < wallSize; i++)
		{
			if (newLoc == walls[i].GetLocation())
			{
				inWall = true;
				break;
			}
		}
	} while (snek.IsinTile(newLoc) || inWall);

	loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
