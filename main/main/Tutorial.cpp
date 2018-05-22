#include "stdafx.h"

#include "Tutorial.h"


Tutorial::Tutorial()
{
}


Tutorial::~Tutorial()
{
}

void Tutorial::init(RenderWindow &window) {
	background.setSize(Vector2f(800, 800));
	if (!backgroundImage.loadFromFile("images/tutorialBackground_800x800.png")) {
		std::cout << "Can't find file - tutorialBackground" << std::endl;
		system("PAUSE");

		window.close();
	}
	background.setTexture(&backgroundImage);

	backButton.setSize(Vector2f(186, 59));
	if (!backButtonImage.loadFromFile("images/backButton_186x59.png")) {
		std::cout << "Can't find file - backButton" << std::endl;
		system("PAUSE");

		window.close();
	}
	backButton.setTexture(&backButtonImage);
	backButton.setOrigin(Vector2f(186, 59));
	backButton.setPosition(Vector2f(788, 788));
}

void Tutorial::mainLoop(RenderWindow &window) {
	Vector2u windowSize;
	Event event;

	windowSize = window.getSize();

	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}

		if (event.type == Event::Resized) {
			window.setSize(Vector2u(800, 800));
		}
	}

	update(window);
	draw(window);
}

void Tutorial::update(RenderWindow &window) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2i mousePosition = Mouse::getPosition(window);

		struct coordinates {
			float x, y;
		} backTL, backBR;

		backBR.x = 788.0f;
		backBR.y = 788.0f;

		backTL.x = backBR.x - 186.0f;
		backTL.y = backBR.y - 59.0f;

		/*std::cout << "x: " << mousePosition.x << " y: " << mousePosition.y << std::endl;*/

		if ((mousePosition.x > backTL.x) && (mousePosition.x < backBR.x) && (mousePosition.y > backTL.y) && (mousePosition.y < backBR.y)) {
			gameState = 0;
		}
	}
}

void Tutorial::draw(RenderWindow &window) {
	window.clear();

	window.draw(background);
	window.draw(backButton);

	window.display();
}