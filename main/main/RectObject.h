#pragma once

#include "Game.h"

#define NUMBER_BOXES 8

using namespace sf;

class RectObject
{
public:
	RectObject();
	~RectObject();

	float angle;
	float angleOfMovement;
	float speed;
	int hits;

	void init(int width);

	void updateSize(int width);
	void move(CircleShape &player, bool isVisible);
	bool checkForCollision(CircleShape &player);
	void draw(RenderWindow &window);

	struct coordinates {
		float x; float y;
	} rectanglePosition;

	RectangleShape boxes[NUMBER_BOXES];

	RectangleShape rectangle;	
};

