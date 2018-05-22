#pragma once

#include "Game.h"

using namespace sf;

class PowerUps
{
public:
	PowerUps();
	~PowerUps();

	float angleOfMovement;
	float angleOfMovementInRadians;
	float speed;

	struct coordinates {
		float x; float y;
	} position;


	void init(Color &main, Color &outline);
	void move();
	void generate();
	void draw(RenderWindow &window);

	bool checkForCollision(CircleShape & player);

private:

	CircleShape circle;
};

