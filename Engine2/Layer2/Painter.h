#pragma once
#include "Layer1.h"


#define TXT_BUFFER_SIZE 4096
using std::string;


class SRGB {
public:
	unsigned char r, g, b,a;
	SRGB (int r, int g, int b): a(255u), r (r), g (g), b (b) {}
	SRGB (Color A):
		a (A >> 24u & 0xFFu),
		r (A >> 16u & 0xFFu),
		g (A >> 8u & 0xFFu),
		b (A >> 0u & 0xFFu){}

	SRGB normalized () {
		SRGB color = (*this);
		int m = (int)minimum (r, g, b);
		return SRGB (r - m, g - m, b - m);
	}

	Color toColor () {
		return r << 16u | g << 8u | b << 0u;
	}

	float distanceFrom (SRGB B) {
		SRGB A = (*this);

		float ABr = (abs (A.r - B.r) / 255.0f); //individual distances
		float ABg = (abs (A.g - B.g) / 255.0f);
		float ABb = (abs (A.b - B.b) / 255.0f);

		return (ABr + ABg + ABb) / 3; //distance average
	}

	float distanceFromN (SRGB B) { //normalized distance
		SRGB A = (*this).normalized ();
		B = B.normalized ();

		float ABr = (abs (A.r - B.r) / 255.0f);
		float ABg = (abs (A.g - B.g) / 255.0f);
		float ABb = (abs (A.b - B.b) / 255.0f);

		return (ABr + ABg + ABb) / 2; //divide by two because 
									  //when normalized, one is always zero
	}

	SRGB colorize (SRGB B, float perc) {
		float q = 1 - perc;
		SRGB copy = (*this);
		copy.r = (B.r *perc + r * q);
		copy.g = (B.g *perc + g * q);
		copy.b = (B.b *perc + b * q);
		return copy;
	}


	SRGB mixInto (SRGB B) {
		float AlphaA = (*this).a / 255.0f;
		return B.colorize ((*this), AlphaA);
	}

};

class Painter {
public:
	void DrawPixelM (int xoff, int yoff, Color c, int m) {

		for (int y = 0; y < m; y++) {
			for (int x = 0; x < m; x++) {

				int finalx = xoff + x;
				int finaly = yoff + y;

				this->DrawPixel (finalx, finaly, c);

			}
		}
	}

	virtual void DrawPixel (int xoff, int yoff, Color c) = 0;
protected:
	virtual Color GetMixColors (Color bck, Color top) {
	
		return SRGB (top).mixInto (SRGB(bck)).toColor();

	}

public:
	void FastHLine (int x, int y, int w, Color c) {
		if (w < 0) {
			x += w;
			w = -w;
		}
		for (int i = 0; i < w; i++) {
			DrawPixel (x + i, y, c);
		}
	}
	void FastVLine (int x, int y, int h, Color c) {
		if (h < 0) {
			y += h;
			h = -h;
		}
		for (int i = 0; i < h; i++) {
			DrawPixel (x, y + i, c);
		}
	}

	void line (int x1, int y1, int x2, int y2, Color c, int width) {
		int r = (0.5f + width) / 2;
		for (int i = 0; i < r; i++) {
			int off = -r / 2 + i;

			line (x1 + off, y1, x2 + off, y2, c);
			line (x1, y1 + off, x2, y2 + off, c);

		}
	}
	void line (int x1, int y1, int x2, int y2, Color c) {
		int dstx = x2 - x1;
		int dsty = y2 - y1;

		DrawPixel (x2, y2, c);
		DrawPixel (x1, y1, c);

		if (dsty == 0 && dstx == 0) {

		}

		else if (abs (dsty) > abs (dstx))
		{
			if (dsty < 0)
			{
				Swap (&x1, &x2);
				Swap (&y1, &y2);
			}

			float m = (float)dstx / (float)dsty;
			float b = x1 - m * y1;
			for (int y = y1; y <= y2; y = y + 1)
			{
				int x = (int)(m*y + b + 0.5f);
				DrawPixel (x, y, c);
			}

		}
		else
		{
			if (dstx < 0)
			{
				Swap (&x1, &x2);
				Swap (&y1, &y2);
			}
			float m = (float)dsty / (float)dstx;
			float b = y1 - m * x1;
			for (int x = x1; x <= x2; x = x + 1)
			{
				int y = (int)(m*x + b + 0.5f);
				DrawPixel (x, y, c);
			}
		}
	}

	void circleBorder (int x0, int y0, int diam, Color c, int width) {
		int rad = diam / 2;
		for (int radius = rad; radius > rad - width; radius--) {
			float r2 = radius * radius;
			int center = (int)(radius * 0.707107f + 0.5f);
			for (int x = 0; x <= center; x++) {

				int y = (int)sqrt ((r2 - x * x));
				for (int i = 0; i < 2; y++, i++) {
					DrawPixel (x0 + x, y0 + y, c);
					DrawPixel (x0 + x, y0 - y, c);
					DrawPixel (x0 + y, y0 + x, c);
					DrawPixel (x0 + y, y0 - x, c);

					DrawPixel (x0 - x, y0 + y, c);
					DrawPixel (x0 - x, y0 - y, c);
					DrawPixel (x0 - y, y0 + x, c);
					DrawPixel (x0 - y, y0 - x, c);
				}

			}
		}
	}
	void circle (int x, int y, int diam, Color c) {
		for (int i = 1; i <= diam; i++) {
			circleBorder (x, y, i, c, diam);
		}

	}

	void rectangleBorder (int x0, int y0, int width, int height, Color c, int r) {
		for (int i = 0; i < r; i++) {
			/*	int off = -r / 2 + i;
			int oss = -r / 2;
			int ose = r;*/

			//	FastHLine(x0 + oss, y0 + off, width + ose, c);
			//	FastHLine(x0 + oss, y0 + off +height, width+ose, c);
			//	FastVLine(x0 + off, y0, height, c);
			//	FastVLine(x0 + off + width, y0, height, c);

			FastHLine (x0 - r + 1, y0 - i, width + r * 2 - 1, c);
			FastHLine (x0 - r + 1, y0 + i + height, width + r * 2 - 1, c);
			FastVLine (x0 - i, y0, height, c);
			FastVLine (x0 + i + width, y0, height, c);
		}
	}
	void rectangle (int xoff, int yoff, int width, int height, Color c) {
		for (int i = 0; i < height; i++) {
			this->FastHLine (xoff, yoff + i, width, c);
		}
	}

	void ellipseBorder (int xoff, int yoff, int width, int height, Color c, int r) {
		for (int i = 0; i < r * 2; i++) {
			int delta = i / 2;
			int iter_xoff = xoff + delta + i % 2;
			int iter_yoff = yoff + delta;

			int size = width * width;
			int hsquared = height * height;
			int fa2 = 4 * size, fb2 = 4 * hsquared;
			int x, y, th;

			y = height;
			th = 2 * hsquared + size * (1 - 2 * height);


			for (x = 0; hsquared*x <= size * y; x++)
			{
				DrawPixel (iter_xoff + x, iter_yoff + y, c);
				DrawPixel (iter_xoff - x, iter_yoff + y, c);
				DrawPixel (iter_xoff + x, iter_yoff - y, c);
				DrawPixel (iter_xoff - x, iter_yoff - y, c);
				if (th >= 0)
				{
					th += fa2 * (1 - y);
					y--;
				}
				th += hsquared * ((4 * x) + 6);
			}

			y = 0;
			th = 2 * size + hsquared * (1 - 2 * width);
			for (x = width; size*y <= hsquared * x; y++)
			{
				DrawPixel (iter_xoff + x, iter_yoff + y, c);
				DrawPixel (iter_xoff - x, iter_yoff + y, c);
				DrawPixel (iter_xoff + x, iter_yoff - y, c);
				DrawPixel (iter_xoff - x, iter_yoff - y, c);
				if (th >= 0)
				{
					th += fb2 * (1 - x);
					x--;
				}
				th += size * ((4 * y) + 6);
			}
		}
	}
	void ellipse (int xoff, int yoff, int width, int height, Color c) {
		for (int y = -height; y <= height; y++) {
			for (int x = -width; x <= width; x++) {
				double dx = (double)x / (double)width;
				double dy = (double)y / (double)height;
				if (dx*dx + dy * dy <= 1)
					DrawPixel (xoff + x, yoff + y, c);
			}
		}
	}

};



class Drawer : protected Painter {

public:
	Painter * paint = this;
	virtual void DrawPixel (int xoff, int yoff, Color c) = 0;
	virtual Color GetPixelAt (int xoff, int yoff) = 0;
	virtual bool DrawIsReady () = 0;

	Color GetPixelResult (Bitmap* Bmp, Pos src, Pos dst) {
		Color pixel = *Bmp->GetPixelPointer (src.x, src.y);
		Color gfxPixel = this->GetPixelAt (dst.x, dst.y);
		SRGB A = pixel;
		SRGB B = Bmp->bckclr;

		float rozdielnost = A.distanceFrom (B);
		Color c = rozdielnost >= Bmp->bckclr_tre ? pixel : gfxPixel;
		return c;

	}

	void DrawBitmap (Bitmap * Bmp, int xoff, int yoff, float mx, float my)
	{
		if (!DrawIsReady ()) { return; }
		if (!(mx > 0 && my > 0)) { return; }

		int draw_width = Bmp->width * mx;
		int draw_height = Bmp->height * my;

		for (int y = 0; y < draw_height; y++) {
			int srcy = y / my;
			for (int x = 0; x < draw_width; x++) {
				int srcx = x / mx;

				Color result = GetPixelResult (Bmp, V2 (srcx, srcy), V2 (xoff + x, yoff + y));
				DrawPixel (xoff + x, yoff + y, result);

			}
		}
	};
	void DrawBitmap (Bitmap* Bmp, int xoff, int yoff) {

		DrawBitmap (Bmp, xoff, yoff, 1, 1);
	}

	void Fill (Color color) {
		rectangle (0, 0, SCREENWIDTH - 1, SCREENHEIGHT - 1, color);
	}


};

class GFXDraw : public Drawer {
public:
	D3DGraphics * gfx;
	int xmin = 0, xmax = SCREENWIDTH, ymin = 0, ymax = SCREENHEIGHT;

	GFXDraw (D3DGraphics* gfx, Pos pos, Size size):gfx (gfx) {
		xmin = pos.x; ymin = pos.y;
		xmax = pos.x + size.x; ymax = pos.y + size.y;

		xmin = (xmin >= 0 && xmin < SCREENWIDTH) ? xmin : 0;
		ymin = (ymin >= 0 && ymin < SCREENHEIGHT) ? ymin : 0;

		xmax = (xmax >= 0 && xmax < SCREENWIDTH) ? xmax : SCREENWIDTH - 1;
		ymax = (ymax >= 0 && ymax < SCREENHEIGHT) ? ymax : SCREENHEIGHT - 1;

	}


	GFXDraw (D3DGraphics* gfx): GFXDraw (gfx, 0, V2 (SCREENWIDTH, SCREENHEIGHT)) {}


	bool DrawIsReady () { return gfx; }

	virtual bool isValid (int xoff, int yoff) {
		if (!gfx ||
			xoff >= xmax ||
			yoff >= ymax ||
			xoff < xmin ||
			yoff < ymin) {
			return false;
		}
		return true;
	}

	Color GetPixelAt (int xoff, int yoff) {
		if (isValid (xoff, yoff)) {
			return gfx->GetPixel (xoff, yoff);
		}
		return Colors::Red;
	}

	void DrawPixel (int xoff, int yoff, Color top) {
		if (isValid (xoff, yoff)) {
			Color bck = this->GetPixelAt (xoff, yoff);
			Color result = GetMixColors (bck, top);
			this->gfx->PutPixel (xoff, yoff, result);
		}
	}
};



class BMPDraw : public Drawer {
public:
	Bitmap * bmp;
	BMPDraw (Bitmap* bmp): bmp (bmp) {}

	bool DrawIsReady () { return true; }

	Color GetPixelAt (int xoff, int yoff) {
		Color * dst = bmp->GetPixelPointer (xoff, yoff);
		if (dst != nullptr) {
			return *dst;
		}
		return Colors::Red;
	}

	void DrawPixel (int xoff, int yoff, Color top) {
		Color *dst = bmp->GetPixelPointer (xoff, yoff);
		Color bck = *dst;
		Color result = GetMixColors (bck, top);

		if (dst != nullptr) {
			*dst = result;
		}
	}
};


