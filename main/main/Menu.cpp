#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::init(RenderWindow &window) {
	// ---------- SETTING THE BACKGROUND ----------
	background.setSize(Vector2f(800, 800));
	if (!backgroundImage.loadFromFile("images/mainMenu_800x800.png")) {
		std::cout << "Can't find file" << std::endl;
		system("PAUSE");

		window.close();
	}
	background.setTexture(&backgroundImage);

	// ---------- SETTING THE BUTTONS ----------
	playButton.setSize(Vector2f(182, 59));
	if (!playButtonImage.loadFromFile("images/playButton_182x59.png")) {
		std::cout << "Can't find file" << std::endl;
		system("PAUSE");

		window.close();
	}
	playButton.setTexture(&playButtonImage);
	playButton.setOrigin(Vector2f(playButton.getSize().x / 2.0f, 0));
	playButton.setPosition(Vector2f(400, 430));

	tutorialButton.setSize(Vector2f(324, 59));
	if (!tutorialButtonImage.loadFromFile("images/tutorialButton_325x59.png")) {
		std::cout << "Can't find file" << std::endl;
		system("PAUSE");

		window.close();
	}
	tutorialButton.setTexture(&tutorialButtonImage);
	tutorialButton.setOrigin(Vector2f(tutorialButton.getSize().x / 2.0f, 0));
	tutorialButton.setPosition(Vector2f(400, 519));
}

void Menu::mainLoop(RenderWindow &window, Game &game) {
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

	update(window, game);
	draw(window);
}

void Menu::update(RenderWindow &window, Game &game) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2i mousePosition = Mouse::getPosition(window);

		struct coordinates {
			float x, y;
		} playTL, playBR, tutorialTL, tutorialBR;

		playTL.x = playButton.getPosition().x - (playButton.getSize().x / 2.0f);
		playTL.y = playButton.getPosition().y;
		playBR.x = playButton.getPosition().x + (playButton.getSize().x / 2.0f);
		playBR.y = playButton.getPosition().y + playButton.getSize().y;

		tutorialTL.x = tutorialButton.getPosition().x - (tutorialButton.getSize().x / 2.0f);
		tutorialTL.y = tutorialButton.getPosition().y;
		tutorialBR.x = tutorialButton.getPosition().x + (tutorialButton.getSize().x / 2.0f);
		tutorialBR.y = tutorialButton.getPosition().y + tutorialButton.getSize().y;

		// ---------- CHECKS WHICH BUTTON HAS BEEN CLICKED ----------
		if ((mousePosition.x > playTL.x) && (mousePosition.x < playBR.x) && (mousePosition.y > playTL.y) && (mousePosition.y < playBR.y)) {
			gamestate = 2; // go to game
			game.reset();
		}
		else if ((mousePosition.x > tutorialTL.x) && (mousePosition.x < tutorialBR.x) && (mousePosition.y > tutorialTL.y) && (mousePosition.y < tutorialBR.y)) {
			gamestate = 1; // go to tutorial
		}
	}
}

void Menu::draw(RenderWindow &window) {
	window.clear();

	window.draw(background);
	window.draw(playButton);
	window.draw(tutorialButton);

	window.display();
}
