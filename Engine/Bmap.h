#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include "Colors.h"
#include "Func.h"

#define ERROR_IO_READ -1
#define ERROR_EMPTY_FILE 1

class BitmapDS {
public:
	
	BitmapDS(int width, int height);
	~BitmapDS();
	int width;
	int height;
	Color * ptr;
};

class Bitmap {
public:
	Bitmap();
	~Bitmap();
	BitmapDS* BitmapData;

	Bitmap* GetBitmapPart(int xoff, int yoff, int WIDTH, int HEIGHT);
	int Load(char* FileName);
	int SetDataSource(BitmapDS* data);
};

class BitmapPart {
	int xoff;
	int yoff;
	int width;
	int height;
};

#endif
