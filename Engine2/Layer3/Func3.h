#pragma once
#include <string>
#include "Vectors.h"
#include "Painter.h"
#include "BitmapFont.h"


#define ALIGN_V  (1)
#define ALIGN_H  (2)
#define ALIGN_VH (3)

void PrintTextAlign (GFXDraw * draw, V2 pos, BitmapFont * font, Size scale, char Align, std::string text);
void PrintText (GFXDraw * draw, Vector2 pos, BitmapFont * font, Size scale, std::string text);