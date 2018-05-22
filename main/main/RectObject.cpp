#include "stdafx.h"
#include "RectObject.h"

#include <iostream>

RectObject::RectObject() {
}

RectObject::~RectObject() {
}

void RectObject::init(int width) {
	srand(time(0));
	float height = width / NUMBER_BOXES;

	RectangleShape tempRectangle(Vector2f(width / NUMBER_BOXES, height));
	tempRectangle.setOutlineColor(Color(255, 255, 255, 0));
	tempRectangle.setOutlineThickness(-1);
	tempRectangle.setFillColor(Color(0, 0, 0, 255));
	
	// ---------- USE SMALLER SQUARE SHAPES TO FIT BIGGER RECTANGLE - FOR BETTER COLLISION ----------
	tempRectangle.setOrigin(Vector2f(width / 2, height / 2));
	boxes[0] = tempRectangle;

	tempRectangle.setOrigin(Vector2f((3 * width) / 8, height / 2));
	boxes[1] = tempRectangle;

	tempRectangle.setOrigin(Vector2f(width / 4, height / 2));
	boxes[2] = tempRectangle;

	tempRectangle.setOrigin(Vector2f(width / 8, height / 2));
	boxes[3] = tempRectangle;

	tempRectangle.setOrigin(Vector2f(0, height / 2));
	boxes[4] = tempRectangle;

	tempRectangle.setOrigin(Vector2f(width / (-8), height / 2));
	boxes[5] = tempRectangle;

	tempRectangle.setOrigin(Vector2f(width / (-4), height / 2));
	boxes[6] = tempRectangle;

	tempRectangle.setOrigin(Vector2f((-3 * width) / 8, height / 2));
	boxes[7] = tempRectangle;

	// ---------- SETTING BIG RECTANGLE THAT THE PLAYER SEES ----------
	tempRectangle.setSize(Vector2f(width, height));
	tempRectangle.setOrigin(Vector2f(width / 2, height / 2));
	tempRectangle.setFillColor(Color(0, 102, 0, 255));
	tempRectangle.setOutlineColor(Color(0, 50, 0, 255));
	tempRectangle.setOutlineThickness(4);
	rectangle = tempRectangle;

	rectanglePosition.x = -800;
	rectanglePosition.y = -800;
	speed = 5;
	angleOfMovement = 135;
	hits = 0;
}

void RectObject::updateSize(int width) { // UPDATES SMALLER SQUARES IF NEED BE
	float height = width / NUMBER_BOXES;

	RectangleShape tempRectangle(Vector2f(width / NUMBER_BOXES, height));
	tempRectangle.setOutlineColor(Color(255, 255, 255, 255));
	tempRectangle.setOutlineThickness(-1);
	tempRectangle.setFillColor(Color(0, 0, 0, 255));

	tempRectangle.setOrigin(Vector2f(width / 2, height));
	boxes[0] = tempRectangle;
	
	tempRectangle.setOrigin(Vector2f((3 * width) / 8, height));
	boxes[1] = tempRectangle;
	
	tempRectangle.setOrigin(Vector2f(width / 4, height));
	boxes[2] = tempRectangle;
	
	tempRectangle.setOrigin(Vector2f(width / 8, height));
	boxes[3] = tempRectangle;
	
	tempRectangle.setOrigin(Vector2f(0, height));
	boxes[4] = tempRectangle;
	
	tempRectangle.setOrigin(Vector2f(width / (-8), height));
	boxes[5] = tempRectangle;
	
	tempRectangle.setOrigin(Vector2f(width / (-4), height));
	boxes[6] = tempRectangle;

	tempRectangle.setOrigin(Vector2f((-3 * width) / 8, height));
	boxes[7] = tempRectangle;

	tempRectangle.setSize(Vector2f(width, height));
	tempRectangle.setOrigin(Vector2f(width / 2, height / 2));
	tempRectangle.setFillColor(Color(0, 50, 0, 128));
	tempRectangle.setOutlineColor(Color(0, 13, 0, 128));
	tempRectangle.setOutlineThickness(4);
	rectangle = tempRectangle;
}

void RectObject::move(CircleShape &player, bool isVisible) {
	float angleOfMovementInRadians = (angleOfMovement / 180) * PI;
	// ---------- USING TRIGONOMETRY TO MOVE SQUARES ----------
	///    Each smaller squares has an origin set to the center of the bigger circle,
	///    with this, the smaller squares rotate on that origin giving the illusion that
	///    they are the BIGGER RECTANGLE
	if (isVisible) {
		if ((abs(rectanglePosition.x - 400) > 450) || (abs(rectanglePosition.y - 400) > 450) || checkForCollision(player)) {
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

			rectanglePosition.x = randX;
			rectanglePosition.y = randY;
		}

		rectanglePosition.x += cos(angleOfMovementInRadians - (PI / 2)) * speed;
		rectanglePosition.y -= sin(angleOfMovementInRadians + (PI / 2)) * speed;

		angle += 2; // MAKES THE SQUARES AND RECTANGLE ROTATE
	}
}

bool RectObject::checkForCollision(CircleShape &player) {
	for (int i = 0; i < NUMBER_BOXES; i++) { // A WAY TO HAVE A BETTER COLLISION WITH A RECTANGLE
		if (player.getGlobalBounds().intersects(boxes[i].getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

void RectObject::draw(RenderWindow &window) {
	for (int i = 0; i < NUMBER_BOXES; i++) {
		boxes[i].setPosition(rectanglePosition.x, rectanglePosition.y);
		boxes[i].setRotation(angle);
		window.draw(boxes[i]);
	}
	
	rectangle.setPosition(rectanglePosition.x, rectanglePosition.y);
	rectangle.setRotation(angle);

	window.draw(rectangle);
}
