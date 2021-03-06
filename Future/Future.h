#pragma once
#include "Interface.h"
#include "FloodfillMap.h"

#include "Vectors.h"
#include "Labelz.h"
#include "Mouse.h"
#include <stdio.h>


class TestInterface : public GFXInterface {
public:
	TestInterface(D3DGraphics* gfx) : GFXInterface(gfx) {}
	void DrawPixelContainer(FloodFillMap* src, int fx, int fy)
	{
		FFPixel* ReadPixel;
		for (int yoff = 0; yoff < src->height; yoff++) {
			for (int xoff = 0; xoff < src->width; xoff++) {

				ReadPixel = src->pixels[yoff* src->width + xoff];

				if (ReadPixel->state & pxstate::checked) {
					paint->DrawPixel(xoff + fx, yoff + fy, 0xFFAC0000);
				}

				else if (ReadPixel->state & pxstate::background) {
					paint->DrawPixel(xoff + fx, yoff + fy, ColorARGB(255, 177, 244, 177));
				}

				else {
					paint->DrawPixel(xoff + fx, yoff + fy, ReadPixel->color);
				}

			}

		}

	}
	void DrawSpritesheet(BitmapArray * sh, int xoff, int yoff)
	{
		int sprw = sh->sprites[0]->width;
		int sprh = sh->sprites[0]->height;


		for (int y = 0; y < sh->hcount; y++) {
			for (int x = 0; x < sh->wcount; x++) {
				int i = y * sh->wcount + x;
				int xdst = x * sprw + 1 * x;
				int ydst = y * sprh + 1 * y;


				this->DrawBitmap(sh->sprites[i], xoff + xdst, yoff + ydst);
				paint->FastVLine(xoff + xdst, yoff + ydst, sprh + 1, 0xFFFFFF);
				paint->FastHLine(xoff + xdst, yoff + ydst, sprw + 1, 0xFFFFFF);
			}
		}


	}
	
};


class Grid {
public:
	int x, y, size;
	int mid;
	const int wc = 20;
	Grid(int x, int y, int size) : x(x), y(y), size(size) { mid = wc / 2; }
	void Draw(Interface * out)
	{
		out->paint->circle(x + mid * size, y + mid * size, 5, Colors::Gray);

		for (int ty = 0; ty < wc; ty++) {
			for (int tx = 0; tx < wc; tx++) {
				out->paint->rectangleBorder(x + tx * size, y + ty * size, size, size, Colors::Black, 1);
			}
		}

	}
};
