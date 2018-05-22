#pragma once

#include "Game.h"

#define PI 3.14159265
#define NUMBER_TRIANGLES 8

using namespace sf;

class TriangleObject
{
public:
	TriangleObject();
	~TriangleObject();

	float angleOfMovement;
	float speed;

	void init(int size);
	void pulse();
	void move(CircleShape &player, bool isVisible);
	void draw(RenderWindow &window);

	bool checkForCollision(CircleShape &player);

	struct coordinates {
		float x; float y;
	} trianglePosition;

private:
	CircleShape triangle;

	int initialSize;

	float step;

};

