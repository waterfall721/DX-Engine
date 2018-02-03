#pragma once
#include "ClickableRectangle.h"
#include "Colors.h"
#include "RasterFont.h"
#include "Interface.h"

class Button : public ClickableRectangle {
public:
	Color clr;
	const static int bfsz = 256;
	char text[bfsz];
	RasterFont* font;
	void(*function)();

	void Draw(Interface* out) {
		int charcnt = strlen(text);
		int textw = charcnt * font->charw;
		out->paint->rectangle(x, y, w, h, clr);

		for (int i = 0; i < 2; i++) {
			out->paint->rectangleBorder(x + i, y + i, w - i * 2, h - i * 2, Colors::Black,2);
		}

		int textY = y + h / 2 - font->charh / 2;
		int textX = x + (this->w- textw) / 2;
		out->PrintText(textX, textY, font, text);

	}

	void RefreshState(MouseClient mouse) {
		this->ClickableRectangle::RefreshState(mouse);
		this->RefreshColors(mouse);

		if (isRelease(mouse)) {
			if (function) {
				function();
			}
		}
	}



	void RefreshColors(MouseClient mouse) {
		clr = Colors::LightGray;
		if (isHover(mouse)) {
			clr = Colors::Gray;
		}
		if (depressed && isHover(mouse)) {
			clr = Colors::Blue;
		}
	}

	Button(int x, int y, int w, int h, char* src, RasterFont* font, void(*function)()) : ClickableRectangle(x, y, w, h), font(font), clr(Colors::LightGray) {
		strcpy_s(text, src);
		text[bfsz - 1] = 0;
		this->function = function;
	}




};