#pragma once


#include "Game.h"

using namespace sf;

class Player
{
public:
	Player();
	~Player();

	bool usingController;
	CircleShape playerShape;
	float playerAngleDegrees;

	void playerMove(RenderWindow &window, float centerX, float centerY);

	struct coordinates {
		float x;
		float y;
	} playerPosition, previousPosition;

private:

	float previousAngle;

};

