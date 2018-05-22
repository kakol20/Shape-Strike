#include "stdafx.h"
#include "CircleObject.h"


CircleObject::CircleObject()
{
}


CircleObject::~CircleObject()
{
}

void CircleObject::init(int size) {
	srand(time(0));
	
	CircleShape tempCircle(size);
	tempCircle.setOrigin(Vector2f(size, size));
	tempCircle.setFillColor(Color(0, 102, 0, 255));
	tempCircle.setOutlineColor(Color(0, 50, 0, 255));
	tempCircle.setOutlineThickness(4);
	circle = tempCircle;

	circlePosition.x = 900;
	circlePosition.y = 900;

	speed = 5;
	angleOfMovement = 135;
}

void CircleObject::move(CircleShape &player, bool isVisible) {
	float angleOfMovementInRadians = (PI / 180) * angleOfMovement;

	if (isVisible) {
		if ((abs(circlePosition.x - 400) > 450) || (abs(circlePosition.y - 400) > 450) || checkForCollision(player)) {
			// ---------- RANDOMLY SETS OBJECT'S POSITION AND ANGLE
			float randX;
			float randY;
			float angleChange = (PI / 180) * ((rand() % 68) - 34);

			int tempInt = rand() % 8;

			// ---------- SPAWNED RANDOMLY OUTSIDE OF THE SCREEN
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

			angleOfMovementInRadians += angleChange; // CHANGES IT ANGLES SLIGHTLY

			if ((angleOfMovementInRadians < 0)) {
				angleOfMovementInRadians += 2 * PI;
			}
			else if (angleOfMovementInRadians >= (2 * PI)) {
				angleOfMovementInRadians -= 2 * PI;
			}

			angleOfMovement = (angleOfMovementInRadians / PI) * 180;

			circlePosition.x = randX;
			circlePosition.y = randY;
		}

		circlePosition.x += cos(angleOfMovementInRadians - (PI / 2)) * speed;
		circlePosition.y -= sin(angleOfMovementInRadians + (PI / 2)) * speed;
	}
}

void CircleObject::draw(RenderWindow &window) {
	circle.setPosition(circlePosition.x, circlePosition.y);

	window.draw(circle);
}

bool CircleObject::checkForCollision(CircleShape &player) {
	if (player.getGlobalBounds().intersects(circle.getGlobalBounds())) {
		return true;
	}
	return false;
}