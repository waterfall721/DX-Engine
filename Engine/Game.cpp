﻿/****************************************************************************************** 
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



Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}


TransparentBitmap img("FONT\\small.bmp");
Spritesheet sh(&img, 16, 16);



TransparentBitmap SpriteImage("SPRITESHEET\\test.bmp");
PixelContainer container;





void Game::Initialise() {
	out.set_graphics(&gfx);
	container.Load(&SpriteImage);


	
}

void Game::ComposeFrame()
{
	container.Draw(&out, 0, 0);

	if (wnd.mouse.LeftIsPressed()) {

		int x = wnd.mouse.GetPosX();
		int y = wnd.mouse.GetPosY();
		if (x < container.width && y < container.height) {
			
			container.CheckPixel(container.pixels[y * container.width + x]);

		}
	}


	if (wnd.mouse.RightIsPressed()) {
		for (int i = 0; i < 500; i++) {
			FFPixel* get = container.GetPending();
			if (get != nullptr) {
				container.CheckPixel(get);
			}
		}
	
		
	}

}

void Game::UpdateModel()
{
}


