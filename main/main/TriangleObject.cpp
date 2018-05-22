#include "stdafx.h"
#include "TriangleObject.h"


TriangleObject::TriangleObject()
{
}


TriangleObject::~TriangleObject()
{
}

void TriangleObject::init(int size) {
	srand(time(0));
	initialSize = size;

	CircleShape tempTriangle(size, 3);
	tempTriangle.setOrigin(Vector2f(size, size));
	tempTriangle.setFillColor(Color(0, 102, 0, 255));
	tempTriangle.setOutlineColor(Color(0, 50, 0, 255));
	tempTriangle.setOutlineThickness(4);
	triangle = tempTriangle;

	trianglePosition.x = 900;
	trianglePosition.y = 900;

	step = 0.0f;
	speed = 5;
	angleOfMovement = 135;
}

void TriangleObject::pulse() {
	// ---------- MAKES TRIANGLE PULSE USING SINE WAVE ----------
	step = step + (1.0f / 8.0f);
	
	float radius = (sin(step) + 2) * initialSize;
	//std::cout << radius << std::endl;

	triangle.setRadius(radius);
	triangle.setOrigin(Vector2f(radius, radius));
}

void TriangleObject::move(CircleShape &player, bool isVisible) {
	float angleOfMovementInRadians = (PI / 180) * angleOfMovement;

	if (isVisible) {
		// ---------- RANDOMLY PLACES TRIANGLE OUTSIDE OF SCREEN ANGLED TOWARDS THE CENTER THEN MODIFIED SLIGHTLY ----------
		if ((abs(trianglePosition.x - 400) > 450) || (abs(trianglePosition.y - 400) > 450) || checkForCollision(player)) {
			float randX;
			float randY;
			float angleChange = (PI / 180) * ((rand() % 68) - 34);

			int tempInt = rand() % 8;

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

			angleOfMovementInRadians += angleChange;

			if ((angleOfMovementInRadians < 0)) {
				angleOfMovementInRadians += 2 * PI;
			}
			else if (angleOfMovementInRadians >= (2 * PI)) {
				angleOfMovementInRadians -= 2 * PI;
			}

			angleOfMovement = (angleOfMovementInRadians / PI) * 180;

			trianglePosition.x = randX;
			trianglePosition.y = randY;
		}

		trianglePosition.x += cos(angleOfMovementInRadians - (PI / 2)) * speed;
		trianglePosition.y -= sin(angleOfMovementInRadians + (PI / 2)) * speed;
	}
}

void TriangleObject::draw(RenderWindow &window) {
	triangle.setPosition(trianglePosition.x, trianglePosition.y);

	window.draw(triangle);
}

bool TriangleObject::checkForCollision(CircleShape &player) {
	if (player.getGlobalBounds().intersects(triangle.getGlobalBounds())) {
		return true;
	}
	return false;
}