#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);
}

void Board::DrawForSnake(const Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension + 1, loc.y * dimension + 1, dimension - 2, dimension - 2, c);
}

void Board::DrawRect(int x, int y, int w, int h, Color c)
{
	gfx.DrawRect(x, y, w, h, c.GetR(), c.GetG(), c.GetB());
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

int Board::getDimension() const
{
	return this->dimension;
}
