#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "Game.h"

using namespace sf;

class Menu
{
public:
	Menu();
	~Menu();

	void init(RenderWindow &window);
	void mainLoop(RenderWindow &window, Game &game);

	int gamestate;

private:
	RectangleShape background, playButton, tutorialButton;

	Texture backgroundImage, playButtonImage, tutorialButtonImage;

	void update(RenderWindow &window, Game &game);
	void draw(RenderWindow &window);
};

