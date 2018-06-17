#pragma once
#include "Button.h"
#include "Colors.h"


class ColorButton : public Button {
public:
	void Draw() override {
		Color drawColor = GetStateColor();
		Vector2 pos = GetAbs();
		draw->paint->rectangle(pos.x, pos.y, size.x, size.y, drawColor);
		draw->paint->rectangleBorder(pos.x, pos.y, size.x, size.y, Colors::Black, 2);

		int textWidth = text.size() * DFONT->charw;
		int textY = pos.y + size.y / 2 - DFONT->charh / 2;
		int textX = pos.x + (size.x - textWidth) / 2;
		PrintText(draw, textX, textY, text,DFONT);

	}

	Color GetStateColor() {
		switch (mregion->state) {
		case MouseState::none:
			return Colors::GrayLightLight;

		case MouseState::pressed:
			return Colors::Gray;

		default:
			return Colors::GrayLight;
		}
	}


	ColorButton(Vector2 position, void(*function)(), string textsrc, Vector2 size) :
		Button(position,size,function,textsrc){
	}



};