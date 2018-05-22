// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h> 
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"
#include "Menu.h"
#include "GameOver.h"
#include "Tutorial.h"

// Documentation and what each class do
// Any comments on any difficulty

using namespace sf;

int gameState;

int main()
{
	srand(time(0));
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	int windowWidth = 800;
	int windowHeight = 800;

	sf::RenderWindow mywindow;
	mywindow.create(sf::VideoMode(windowWidth, windowHeight), "Shape Strike", Style::Close, settings);
	mywindow.setFramerateLimit(60);

	Menu menu;
	Game game;
	Tutorial tutorial;
	GameOver gameOver;

	gameState = 0;
	menu.gamestate = gameState;
	game.gameState = gameState;
	tutorial.gameState = gameState;
	gameOver.gameState = gameState;

	menu.init(mywindow);
	game.init(mywindow);
	tutorial.init(mywindow);
	gameOver.init(mywindow);

	Music mus;
	if (!mus.openFromFile("sound/Space Fighter Loop.ogg")) {
		std::cout << "Can't load sound file" << std::endl;
	}
	mus.setVolume(25);
	mus.setLoop(true);
	mus.play();

	while (mywindow.isOpen()) {	
		switch (gameState) {
			case 0: // main menu
				menu.mainLoop(mywindow, game);

				gameState = menu.gamestate;
				game.gameState = gameState;
				tutorial.gameState = gameState;

				break;

			case 1: // tutorial
				tutorial.mainLoop(mywindow);

				gameState = tutorial.gameState;
				menu.gamestate = gameState;

				break;

			case 2: // game

				game.mainLoop(mywindow, gameOver);

				gameState = game.gameState;
				menu.gamestate = gameState;
				gameOver.gameState = gameState;

				break;
			
			case 3: // game over
				gameOver.mainLoop(mywindow);

				gameState = gameOver.gameState;
				menu.gamestate = gameState;

				break;

			default: 
				break;
		}
	}

	system("PAUSE");
	return 0;
}

