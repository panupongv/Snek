#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
	constexpr int numBodyColor = 4;
	constexpr Color bodyColors[numBodyColor] = {
	{10, 100, 32},
	{10, 130, 32},
	{10, 160, 32},
	{10, 130, 32} };
	for (int i = numSegmentMax ; i > 0; i--)
	{
		segments[i].InitBody(bodyColors[i % numBodyColor]);
	}
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = numSegment - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}
	
void Snake::Grow()
{
	if (numSegment < numSegmentMax)
	{
		this->numSegment++;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < numSegment; i++)
		segments[i].Draw(brd);
}

bool Snake::IsinTileExceptEnd(const Location & target) const
{
	for (int i = 0; i < numSegment - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsinTile(const Location & target) const
{
	for (int i = 0; i < numSegment; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location & loc)
{
	this->loc = loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color c)
{
	this->c = c;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawForSnake(loc, c);
}

const Location Snake::Segment::GetLocation() const
{
	return loc;
}
