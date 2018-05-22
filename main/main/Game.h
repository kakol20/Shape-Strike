#pragma once

#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <Math.h>
#include <random>
#include <cmath>
#include <ctime>
#include <stdlib.h>


#include "Player.h"
#include "RectObject.h"
#include "TriangleObject.h"
#include "CircleObject.h"
#include "PowerUps.h"
#include "Arc.h"

#include "GameOver.h"


#define PI 3.14159265 

#define MAX_RECT 3
#define MAX_TRIANGLE 3
#define MAX_CIRCLE 3

using namespace sf;

class Game
{
public:
	Game();
	~Game();

	void init(RenderWindow &window);
	void mainLoop(RenderWindow &window, GameOver &gameOver);
	void reset();

	int gameState;
	int score;
	int highscore;

private:
	struct coordinates {
		float x;
		float y;
	} centerPosition, healthGetPosition;

	CircleShape center;
	Font font;
	Text scoreText, healthText, instructions, vulnerableTime, plusOne, minusOne, plusOneScore, escToExit;

	time_t timeLast, timeNow, startTime, timeLast2, timeLast3;
	double dif;
	
	int numberOfRectObjects;
	int numberOfTriangleObjects;
	int numberOfCircleObjects;
	int health;
	
	float vulnerableTimeLeft;

	bool vulnerable;

	RectangleShape gameBackground;
	Texture backgroundImage;

	RectangleShape healthbarBack, healthbarFront;

	int plusHealthBias = 1, invulnerabilityBias = 1;

	void update(RenderWindow &window, GameOver &gameOver), draw(RenderWindow &window);
};

