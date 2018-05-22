#pragma once

#include "Game.h"

class ArcDraw
{
public:
	ArcDraw();
	~ArcDraw();
	
	void draw(int x, int y, float r, float sAngle, float eAngle, int lineWidth, Color &color, RenderWindow &window);

	//RectangleShape line(Vector2f(150,))
};

