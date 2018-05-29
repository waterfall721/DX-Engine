#pragma once
#include "Element.h"
#include "GlobalObjects.h"
#include "MouseRegion.h"

class CheckBox : public BaseElement, public PosElement {
public:
	bool checked = false;
	const int radius = 15;
	std::string text = "";
	MouseRegion mregion;

	void Toggle() {
		checked = !checked;
	}

	CheckBox(Vector2 position, const char* text): 
		PosElement(position), mregion(position, Vector2(30,30))
	{
		this->text = text;
		Vector2 size = Vector2(radius * 2, radius * 2);
	//	mregion.function = &Toggle;
	}



	void Draw() {
		Vector2 pos = GetAbs();

		io->out->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::White);
		if (checked) {
			io->out->paint->rectangle(pos.x, pos.y, radius * 2, radius * 2, Colors::GreenDark);
			io->out->paint->line(pos.x, pos.y, pos.x + radius * 2, pos.y + radius * 2, Colors::White,2);
			io->out->paint->line(pos.x, pos.y + radius * 2, pos.x + radius * 2, pos.y , Colors::White,2);

		
		}
		io->out->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::Black, 3);
		io->out->paint->rectangleBorder(pos.x, pos.y, radius * 2, radius * 2, Colors::White, 1);
		io->out->PrintText(pos.x + radius * 2.34, pos.y + radius /3, DFONT, text);


	}


};