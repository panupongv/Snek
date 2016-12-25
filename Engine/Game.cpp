/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({2, 2}),
	goal(rng, brd, snek, walls, numWall)
{
	int current = 0;
	for (int i = 0; i < brd.GetGridWidth(); i++)
	{
			walls[current].Init(i, 0);
			current++;
	}
	for (int i = 0; i < brd.GetGridWidth(); i++)
	{
		walls[current].Init(i, brd.GetGridHeight() - 1);
		current++;
	}

	for (int i = 0; i < brd.GetGridHeight(); i++)
	{
		walls[current].Init(0, i);
		current++;
	}
	for (int i = 0; i < brd.GetGridHeight(); i++)
	{
		walls[current].Init(brd.GetGridWidth() - 1, i);
		current++;
	}
	while (current < numWall)
	{
		walls[current].Init(rng, brd, snek);
		current++;
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			if(delta_loc.y != 1)
				delta_loc = { 0, -1 };
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			if (delta_loc.y != -1)
				delta_loc = { 0, 1 };
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			if (delta_loc.x != 1)
			delta_loc = { -1, 0 };
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			if (delta_loc.x != -1)
				delta_loc = { 1, 0 };
		}
		snekMoveCounter++;
		if (snekMoveCounter > snekMovePeriod)
		{
			snekMoveCounter = 0;
			const Location next = snek.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || 
				snek.IsinTileExceptEnd(next))
			{
				gameOver = true;
			}
			else
			{
				bool eating = next == goal.GetLocation();
				if (eating)
				{
					snek.Grow();
				}
				snek.MoveBy(delta_loc);
				if (eating)
				{
					goal.Respawn(rng, brd, snek, walls, numWall);

				}
				for (int i = 0; i < numWall; i++)
				{
					if (next == walls[i].GetLocation())
					{
						gameOver = true;
						break;
					}
				}
			}
		}
		if (snekMovePeriod > snekMpvePeriodMin)
		{
			snekSpeedUpCounter++;
			if (snekSpeedUpCounter >= snekSpeedUpPeriod)
			{
				snekSpeedUpCounter = 0;
				snekMovePeriod--;
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (gameOver)
		SpriteCodex::DrawGameOver(200, 200, gfx);
	snek.Draw(brd);
	goal.Draw(brd);
	for (int i = 0; i < numWall; i++)
	{
		walls[i].Draw(brd);
	}
}
