#ifndef __GRAPHICAL_H__
#define __GRAPHICAL_H__
#include "Interface.h"

class Interface;
class Draw {
public:
	Interface*  out;

public:
	void setOutInterface(Interface* out);

	void FastHLine(int x, int y, int w, Color c); 
	void FastVLine( int x, int y, int h, Color c);
	void circle( int x, int y, int rad, Color c);
	void line(int x1, int y1, int x2, int y2, Color c);
	void rectangle( int x, int y, int w, int h, Color c);
	void rectangle_fill(int x, int y, int w, int h, Color c);
};


#endif 
