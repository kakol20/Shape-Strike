#include "stdafx.h"
#include "PowerUps.h"


PowerUps::PowerUps()
{
}


PowerUps::~PowerUps()
{
}

void PowerUps::init(Color &main, Color &outline) {
	srand(time(0));
	// ---------- CREATES SPRITE ----------
	CircleShape tempCircle(12);
	tempCircle.setOrigin(Vector2f(12, 12));
	tempCircle.setFillColor(main);
	tempCircle.setOutlineColor(outline);
	tempCircle.setOutlineThickness(4);
	circle = tempCircle;

	position.x = 900;
	position.y = 900;

	speed = 5;
	angleOfMovement = 135;
}

void PowerUps::generate() {
	float randX;
	float randY;

	int tempInt = rand() % 8;

	// ---------- RANDOMLY GENERATES POSITION OUTSIDE OF SCREEN AND ANGLE TOWARDS CENTER ----------
	if (tempInt == 7) {
		randX = (rand() % 425) - 25;
		randY = -25;

		angleOfMovementInRadians = atan((400 - randY) / (400 - randX)) + (PI / 2);
	}
	else if (tempInt == 6) {
		randX = -25;
		randY = (rand() % 425) - 25;

		angleOfMovementInRadians = PI - atan((400 - randX) / (400 - randY));
	}
	else if (tempInt == 5) {
		randX = -25;
		randY = (rand() % 425) + 400;

		angleOfMovementInRadians = atan((400 - randX) / (randY - 400));
	}
	else if (tempInt == 4) {
		randX = (rand() % 425) - 25;
		randY = 825;

		angleOfMovementInRadians = (PI / 2) - atan((randY - 400) / (400 - randX));
	}
	else if (tempInt == 3) {
		randX = (rand() % 425) + 400;
		randY = 825;

		angleOfMovementInRadians = ((3 * PI) / 2) + atan((randY - 400) / (randX - 400));
	}
	else if (tempInt == 2) {
		randX = 825;
		randY = (rand() % 425) + 400;

		angleOfMovementInRadians = (2 * PI) - atan((randX - 400) / (randY - 400));
	}
	else if (tempInt == 1) {
		randX = 825;
		randY = (rand() % 425) - 25;

		angleOfMovementInRadians = PI + atan((randX - 400) / (400 - randY));
	}
	else {
		randX = (rand() % 425) + 400;
		randY = -25;

		angleOfMovementInRadians = ((3 * PI) / 2) - atan((400 - randY) / (randX - 400));
	}

	angleOfMovement = (angleOfMovementInRadians / PI) * 180;
	position.x = randX;
	position.y = randY;
}

void PowerUps::move() {
	// ---------- USING TRIGONOMETRY TO MOVE SPRITE ----------
	angleOfMovementInRadians = (PI / 180) * angleOfMovement;

	position.x += cos(angleOfMovementInRadians - (PI / 2)) * speed;
	position.y -= sin(angleOfMovementInRadians + (PI / 2)) * speed;
}

void PowerUps::draw(RenderWindow &window) {
	circle.setPosition(position.x, position.y);

	window.draw(circle);
}

bool PowerUps::checkForCollision(CircleShape &player) {
	if (player.getGlobalBounds().intersects(circle.getGlobalBounds())) {
		return true;
	}
	return false;
}
