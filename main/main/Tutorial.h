#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

using namespace sf;

#define PI 3.14159265
class Tutorial
{
public:
	Tutorial();
	~Tutorial();

	void init(RenderWindow &window);
	void mainLoop(RenderWindow &window);

	int gameState;

private: 

	RectangleShape background, backButton;

	Texture backgroundImage, backButtonImage;

	void update(RenderWindow &window);
	void draw(RenderWindow &window);
};

