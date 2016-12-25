#pragma once

#include "Board.h"
#include "Location.h"


class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd) const;
	bool IsinTileExceptEnd(const Location& target) const;
	bool IsinTile(const Location& target) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	
	static constexpr int numSegmentMax = 100;
	Segment segments[numSegmentMax];
	int numSegment = 1;
};