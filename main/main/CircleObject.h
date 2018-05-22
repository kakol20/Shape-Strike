#pragma once

#include "Game.h"

#define NUMBER_CIRCLES 8

using namespace sf;

class CircleObject
{
public:
	CircleObject();
	~CircleObject();

	float angleOfMovement;
	float speed;

	void init(int size);
	//void pulse();
	void move(CircleShape &player, bool isVisible);
	void draw(RenderWindow &window);

	bool checkForCollision(CircleShape &player);

	struct coordinates {
		float x; float y;
	} circlePosition;

private:
	CircleShape circle;

	//int initialSize;

	//float step;

};

