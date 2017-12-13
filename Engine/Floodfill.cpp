#include "Floodfill.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>  

void PixelContainer::Draw(Interface * out, int fx, int fy)
{

	int color_background = Color(0,0,0).dword; //black
	int color_checked = Color(51, 204, 51).dword; //green
	int color_stalled = Color(102, 102, 153).dword; //gray

	FFPixel* ReadPixel;
	for (int yoff = 0; yoff < height; yoff++) {
		for (int xoff = 0; xoff < width; xoff++) {

			ReadPixel = pixels[yoff* width + xoff];
	
			if (ReadPixel->state & pxstate::checked) {
				out->DrawPixel(xoff + fx, yoff + fy, 0xFF0000);
			}

			else if (ReadPixel->state & pxstate::background) {
				out->DrawPixel(xoff + fx, yoff + fy, color_background);
			}

			else {
				out->DrawPixel(xoff + fx, yoff + fy, ReadPixel->color);
			}

		}
	
	}

}

FFPixel * PixelContainer::GetNextSpritePixel()
{
	for (int i = lastpos; i < get_pixelcount(); i++) {
		if (!(pixels[i]->state & pxstate::skip)) {
			lastpos = i;
			return pixels[i];
		}
	}

	return nullptr;
}



vector<FPixel*>* PixelContainer::GetGroupFrom(FFPixel* pixel) {
	if (!pixel) return nullptr;

	this->CheckPixel(pixel);

	while (stalledPixels.size() > 0) {
		FFPixel* result = stalledPixels.back();
		stalledPixels.pop_back();
		this->CheckPixel(result);
	}

	vector<FPixel*>* result = nullptr;

	if (temp_checks.size() > 0) {
		result = new vector<FPixel*>;
	}

	for (std::vector<FFPixel*>::iterator it = temp_checks.begin(); it != temp_checks.end(); ++it)
	{
		FFPixel* current = *it;
		result->push_back(new FPixel(*current));
		delete *it;
	}


	temp_checks.clear();

	return result;
}

vector<FPixel*>* PixelContainer::GetNextSpriteGroup()
{
	return GetGroupFrom(GetNextSpritePixel());
}





FFPixel * PixelContainer::getPixelAt(int x, int y)
{
	if (x >= 0 && 
		y >= 0 &&
	    x < width && 
	    y < height) {
		return this->pixels[y*width + x];
	}

	return nullptr;
}





void PixelContainer::CheckPixel(FFPixel* pixel) {
	if (pixel->state & pxstate::skip) {
		return;
	}

	pixel->state |= pxstate::checked;

	const int neighborcount= 4;
	FFPixel* neighbors[neighborcount] = {
		getPixelAt(pixel->x - 1, pixel->y),
		getPixelAt(pixel->x + 1, pixel->y),
		getPixelAt(pixel->x, pixel->y - 1),
		getPixelAt(pixel->x, pixel->y + 1)
	};

	for (int i = 0; i < neighborcount; i++) {
		if (!neighbors[i]) { continue; }

		if (!(neighbors[i]->state & pxstate::skip)) {
			stalledPixels.push_back(neighbors[i]);
		}
	}

	this->temp_checks.push_back(pixel);


}


void PixelContainer::Load(Bitmap * bmp)
{
	this->width = bmp->width;
	this->height = bmp->height;
	this->pixels = new FFPixel*[get_pixelcount()];


	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			int i = y*width + x;
			Color c = bmp->data[i];

			int state = 0;
			if (bmp->IsColorTransparent(c)) {
				state |= pxstate::background;
			}
			
			pixels[i] = new FFPixel(x, y, c, state);

		}
	}

}

