#include "stdafx.h"
#include "Player.h"

#include <iostream>

#define PI 3.14159265

Player::Player()
{
	CircleShape tempCircle(12);
	tempCircle.setOrigin(Vector2f(12, 12));
	tempCircle.setFillColor(Color(0, 102, 102));
	tempCircle.setOutlineThickness(4);
	tempCircle.setOutlineColor(Color(0, 50, 50));
	playerPosition.x = 400 * PI;
	playerPosition.y = 325;
	tempCircle.setPosition(playerPosition.x, playerPosition.y);
	playerShape = tempCircle;

	previousAngle = 0;
}


Player::~Player()
{
}

void Player::playerMove(RenderWindow &window, float centerX, float centerY) {
	Vector2i mousePosition = Mouse::getPosition(window);
	int distance = 75;

	float angleRadians = 0;

	playerPosition.x = centerX;
	playerPosition.y = centerY;

	// ---------- ANGLES THE PLAYER SPRITE ----------
	if (usingController && Joystick::isConnected(0)) {
		float x = Joystick::getAxisPosition(0, Joystick::U);
		float y = Joystick::getAxisPosition(0, Joystick::R);
		/*std::cout << x << std::endl;*/

		if ((x < 0.5) && (x > 0.0) ) {
			x = 0.0;
		}

		if ((y < 0.5) && (y > 0.0)) {
			y = 0.0;
		}

		if ((y == 0) && (x == 0)) {
			angleRadians = previousAngle;
		}
		else if ((y > 0.0) && (x == 0.0)) {
			angleRadians = PI;
		}
		else if ((y < 0.0) && (x == 0.0)) {
			angleRadians = 0;
		}
		else if (x > 0.0) {
			angleRadians = atan((0 - y) / x);
			angleRadians = (PI / 2) - angleRadians;
		}
		else {
			angleRadians = atan((0 - y) / (-1 * x));
			angleRadians = ((3 * PI) / 2) + angleRadians;
		}
	}
	else {
		if ((mousePosition.y > centerY) && (mousePosition.x == centerX)) {
			angleRadians = PI;
		}
		else if ((mousePosition.y <= centerY) && (mousePosition.x == centerX)) {
			angleRadians = 0;
		}
		else if (mousePosition.x > centerX) {
			angleRadians = atan((centerY - mousePosition.y) / (mousePosition.x - centerX));
			angleRadians = (PI / 2) - angleRadians;
		}
		else {
			angleRadians = atan((centerY - mousePosition.y) / (-1 * (mousePosition.x - centerX)));
			angleRadians = ((3 * PI) / 2) + angleRadians;
		}
	}
	if (angleRadians < 0) {
		angleRadians = (2 * PI) + angleRadians;
	}

	playerAngleDegrees = (180 / PI) * angleRadians;

	// ---------- USING TRIGONOMETRY TO WORK OUR SPRITE POSITION BASED ON ANGLE ----------
	playerPosition.x += (cos(angleRadians - (PI / 2)) * distance);
	playerPosition.y -= (sin(angleRadians + (PI / 2)) * distance);

	playerShape.setPosition(playerPosition.x, playerPosition.y);
	playerPosition = previousPosition;

	previousAngle = angleRadians;
} 
