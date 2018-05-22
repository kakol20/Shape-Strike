#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

void GameOver::init(RenderWindow &window) {
	// ---------- SETTING THE BACKGROUND ----------
	background.setSize(Vector2f(800, 800));
	if (!backgroundImage.loadFromFile("images/gameOverBackground_800x800.png")) {
		std::cout << "Can't load file" << std::endl;
		system("PAUSE");

		window.close();
	}
	background.setTexture(&backgroundImage);

	// ---------- SETTING THE TEXT ----------
	if (!font.loadFromFile("fonts/Etho.ttf")) {
		std::cout << "Can't load font" << std::endl;
		system("PAUSE");

		window.close();
	}
	
	yourScore.setFont(font);
	yourScore.setCharacterSize(30);
	yourScore.setString("Your score: %d");
	yourScore.setFillColor(Color(0, 102, 0));
	yourScore.setOutlineThickness(4);
	yourScore.setOutlineColor(Color(0, 50, 0));
	FloatRect textRect = yourScore.getLocalBounds();
	yourScore.setOrigin(Vector2f(textRect.width / 2.0f, 0));
	yourScore.setPosition(Vector2f(400, 430));

	highScore.setFont(font);
	highScore.setCharacterSize(30);
	highScore.setString("Highscore: %d");
	highScore.setFillColor(Color(0, 102, 0));
	highScore.setOutlineThickness(4);
	highScore.setOutlineColor(Color(0, 50, 0));
	textRect = highScore.getLocalBounds();
	highScore.setOrigin(Vector2f(textRect.width / 2.0f, 0));
	highScore.setPosition(Vector2f(400, 466));

	// ---------- SETTING THE BUTTON ----------
	button.setSize(Vector2f(366, 59));
	if (!buttonImage.loadFromFile("images/gameOverButton_366x59.png")) {
		std::cout << "Can't load font" << std::endl;
		system("PAUSE");

		window.close();
	}
	button.setTexture(&buttonImage);
	button.setOrigin(Vector2f(button.getSize().x / 2.0f, 0));
	button.setPosition(Vector2f(400, 729));
}

void GameOver::reset(int yScore, int hScore) {
	char yScoreText[20];
	sprintf_s(yScoreText, "Your score: %d", yScore);
	yourScore.setString(yScoreText);

	char hScoreText[20];
	sprintf_s(hScoreText, "High score: %d", hScore);
	highScore.setString(hScoreText);
}

void GameOver::mainLoop(RenderWindow &window) {
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

void GameOver::update(RenderWindow &window) {
	// ---------- CHECKS IF THE BUTTON HAS BEEN PRESSED ----------
	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2i mouse = Mouse::getPosition(window);

		struct coordinates {
			float x, y;
		} buttonTL, buttonBR;

		buttonTL.x = button.getPosition().x - (button.getSize().x / 2.0f);
		buttonTL.y = button.getPosition().y;

		buttonBR.x = buttonTL.x + button.getSize().x;
		buttonBR.y = buttonTL.y + button.getSize().y;

		if ((mouse.x > buttonTL.x) && (mouse.x < buttonBR.x) && (mouse.y > buttonTL.y) && (mouse.y < buttonBR.y)) {
			gameState = 0;
		}
	}
}

void GameOver::draw(RenderWindow &window) {
	window.clear();

	window.draw(background);
	window.draw(yourScore);
	window.draw(highScore);
	window.draw(button);

	window.display();
}