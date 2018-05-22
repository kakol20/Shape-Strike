#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

using namespace sf;

class GameOver
{
public:
	GameOver();
	~GameOver();

	void init(RenderWindow &window);
	void mainLoop(RenderWindow &window);
	void reset(int yScore, int hScore);

	int gameState;

private:
	void update(RenderWindow &window);
	void draw(RenderWindow &window);

	RectangleShape background, button;
	Texture backgroundImage, buttonImage;

	Font font;
	Text yourScore, highScore;
};

