#ifndef __VBMP_H__
#define __VBMP_H__
#include <vector>
#include "Bmap.h"
using std::vector;


class FPixel {
public:
	int x, y;
	Color color;
	FPixel(int x, int y, Color c) : x(x), y(y), color(c) {}
};

class Bitmap;
class MySprite {

protected:
	int offx, offy;

public:
	int width, height;
	std::vector<FPixel*>* pixels;

public:
	MySprite(vector<FPixel*>* src);
	MySprite(TransparentBitmap* src);
	void ComputeSize();
	void NormalizeV();
	void NormalizeH();
	~MySprite();

};

#endif