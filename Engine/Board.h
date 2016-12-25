#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawForSnake(const Location& loc, Color c);
	void DrawRect(int x, int y, int w, int h, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	int getDimension() const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
	Graphics& gfx;
};