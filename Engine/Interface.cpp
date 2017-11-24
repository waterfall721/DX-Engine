#include "Interface.h"

void Interface::set_graphics(Graphics* gfx) { 
	this->gfx = gfx; 
	if (gfx != nullptr) {
		Graphics_loaded = YES;
	}
}
void Interface::DrawPixel(int x, int y, Color c) { 
	if (!(Graphics_loaded == YES)) {
		return;
	}
	gfx->PutPixel(x, y, c);
	
}

/*void Interface::DrawText(char * str, int x, int y)
{
	
	double POS_COUNTER = 0;
	
	//cache variables
	int BASE_W;
	Bitmap*  B;
	this->TextObj->setText(str);
	char* ptr = &TextObj->text[0];
		
	while(*ptr++ != 0){
		B = TextObj->Get_Bitmap_Char(* (ptr - 1));
		BASE_W = B->width;
		Draw_Bitmap(B, x + (int) POS_COUNTER, y);
		POS_COUNTER += BASE_W * 0.65;

		if (*ptr >= '0' && *ptr <= '9') POS_COUNTER += BASE_W * 0.20;
		else if (*ptr >= 'A' && *ptr <= 'Z') POS_COUNTER += BASE_W * 0.05;
	}

}

void Interface::set_font(Text * txt)
{
	this->TextObj = txt;
}
*/
void Interface::Draw_Bitmap(Bitmap* B, int fx, int fy) {
	
	for (int y = 0; y < B->BitmapData->height; y++) {
		for (int x = 0; x < B->BitmapData->width; x++) {

			READ_COLOR = B->BitmapData->ptr[y* B->BitmapData->width + x];
			DrawPixel(x + fx, y + fy, READ_COLOR);
			
			
		}
	}
}
