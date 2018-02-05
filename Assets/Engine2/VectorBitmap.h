#ifndef __VBMP_H__
#define __VBMP_H__
#include "Bmap.h"
#include <vector>
using std::vector;

class FPixel {
public:
	int x, y;
	Color color;
	FPixel(int x, int y, Color c) : x(x), y(y), color(c) {}
};

class FPixelMap {

protected:
	int offx, offy;

public:
	int width, height;
	std::vector<FPixel*>* pixels;

public:
	FPixelMap(vector<FPixel*>* src);
	FPixelMap(Bitmap* src);
	void ComputeSize();
	void NormalizeV();
	void NormalizeH();
	~FPixelMap();

};

#endif