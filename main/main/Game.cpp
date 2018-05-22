#include "stdafx.h"
#include "Game.h"

using namespace sf;

Player player;
RectObject rectangleObjects[MAX_RECT];
TriangleObject triangleObjects[MAX_TRIANGLE];
CircleObject circleObjects[MAX_CIRCLE];
PowerUps extraHealth, invulnerability;
ArcDraw arc;

Game::Game()
{
}


Game::~Game()
{
}

void Game::reset() { // RESETS EVERYTHING
	srand(time(0));
	time(&timeLast);
	time(&startTime);
	time(&timeLast2);
	health = 20;
	score = 0;
	numberOfRectObjects = 0;
	numberOfTriangleObjects = 0;
	numberOfCircleObjects = 0;
	plusHealthBias = 1;
	invulnerabilityBias = 1;

	for (int i = 0; i < MAX_RECT; i++) {
		rectangleObjects[i].rectanglePosition.x = -800;
		rectangleObjects[i].rectanglePosition.y = -800;
		rectangleObjects[i].angleOfMovement = 0;
	}

	for (int i = 0; i < MAX_CIRCLE; i++) {
		circleObjects[i].circlePosition.x = -800;
		circleObjects[i].circlePosition.y = -800;
		circleObjects[i].angleOfMovement = 0;
	}

	for (int i = 0; i < MAX_TRIANGLE; i++) {
		triangleObjects[i].trianglePosition.x = -800;
		triangleObjects[i].trianglePosition.y = -800;
		triangleObjects[i].angleOfMovement = 0;
	}

	// ---------- RANDOMLY CHOOSES WHICH OBJECT TO SPAWN ----------
	RectObject tempRect;
	TriangleObject tempTriangle;
	CircleObject tempCircleObj;
	int choose = rand() % 3;
	switch (choose) {
	case 0:
		numberOfRectObjects = 1;
		tempRect.init(100);
		for (int i = 0; i < numberOfRectObjects; i++) {
			rectangleObjects[i] = tempRect;
		}
		break;
	case 1:
		numberOfTriangleObjects = 1;
		tempTriangle.init(15);
		for (int i = 0; i < numberOfTriangleObjects; i++) {
			triangleObjects[i] = tempTriangle;
		}
		break;
	case 2:
		numberOfCircleObjects = 1;
		tempCircleObj.init(12);
		for (int i = 0; i < numberOfCircleObjects; i++) {
			circleObjects[i] = tempCircleObj;
		}
		break;
	}

	// ---------- RESETS TO OUTSIDE OF THE SCREEN ----------
	minusOne.setPosition(Vector2f(-800, -800));
	plusOne.setPosition(Vector2f(-800, -800));
	plusOneScore.setPosition(Vector2f(-800, -800));

	extraHealth.position.x = -800;
	extraHealth.position.y = -800;
	extraHealth.angleOfMovement = 0;

	invulnerability.position.x = -800;
	invulnerability.position.y = -800;
	invulnerability.angleOfMovement = 0;
	vulnerable = true;
}

void Game::init(RenderWindow &window) {
	srand(time(0));
	time(&timeLast);
	time(&startTime);
	time(&timeLast2);
	health = 20;
	score = 0;
	numberOfRectObjects = 0;
	numberOfTriangleObjects = 0;
	numberOfCircleObjects = 0;
	highscore = 0;

	// Background and Text
	RectangleShape background(Vector2f(800, 800));
	
	if (!backgroundImage.loadFromFile("images/background_800x800.png")) {
		std::cout << "Can't find file" << std::endl;
		system("PAUSE");

		window.close();
	}
	background.setTexture(&backgroundImage);
	gameBackground = background;
	gameBackground.setOrigin(Vector2f(background.getSize().x / 2, background.getSize().y / 2));
	gameBackground.setPosition(Vector2f(400, 
		400));

	// ---------- ON SCREEN TEXT ----------	
	if (!font.loadFromFile("fonts/Etho.ttf")) {
		std::cout << "Invalid font file" << std::endl;
		system("PAUSE");

		window.close();
	}

	player.usingController = false;

	instructions.setFont(font);
	//instructions.setString("Use mouse to play");
	if (player.usingController) {
		instructions.setString("Use the RS to play");
	}
	else {
		instructions.setString("USE MOUSE TO PLAY");
	}

	instructions.setCharacterSize(30);
	instructions.setFillColor(Color(0, 102, 0));
	//instructions.setStyle(Text::Bold);
	instructions.setOutlineColor(Color(0, 50, 0));
	instructions.setOutlineThickness(4);
	FloatRect textRect = instructions.getLocalBounds();
	instructions.setOrigin(Vector2f(textRect.width / 2.0f, 0));
	instructions.setPosition(400, 12);

	escToExit.setFont(font);
	escToExit.setCharacterSize(20);
	escToExit.setString("Esc to exit");
	escToExit.setFillColor(Color(0, 102, 0));
	escToExit.setOutlineColor(Color(0, 50, 0));
	escToExit.setOutlineThickness(4);
	textRect = escToExit.getLocalBounds();
	escToExit.setOrigin(Vector2f(textRect.width / 2.0f, 0));
	escToExit.setPosition(400, 48);

	scoreText.setFont(font);

	char tempString[50];
	//int tempInt = score;
	sprintf_s(tempString, "Score: %d", score);
	scoreText.setString(tempString);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(Color(0, 102, 0));
	//scoreText.setStyle(Text::Bold);
	scoreText.setOutlineColor(Color(0, 50, 0));
	scoreText.setOutlineThickness(4);
	textRect = scoreText.getLocalBounds();
	scoreText.setOrigin(Vector2f(0, textRect.height));
	scoreText.setPosition(12, 788);

	// ---------- SCORE/HEALTH CHANGE INDICATORS ----------

	plusOne.setFont(font);
	plusOne.setString("+1 Health");
	plusOne.setCharacterSize(30);
	plusOne.setFillColor(Color(0, 102, 0));
	//plusOne.setStyle(Text::Bold);
	plusOne.setOutlineColor(Color(0, 50, 0));
	plusOne.setOutlineThickness(4);
	textRect = plusOne.getGlobalBounds();
	plusOne.setOrigin(Vector2f(textRect.width / 2.0f, textRect.height));
	plusOne.setPosition(-100, -100);

	minusOne.setFont(font);
	minusOne.setString("-1 Health");
	minusOne.setCharacterSize(30);
	minusOne.setFillColor(Color(0, 102, 0));
	//minusOne.setStyle(Text::Bold);
	minusOne.setOutlineColor(Color(0, 50, 0));
	minusOne.setOutlineThickness(4);
	textRect = minusOne.getGlobalBounds();
	minusOne.setOrigin(Vector2f(textRect.width / 2.0f, textRect.height));
	minusOne.setPosition(-100, -100);

	plusOneScore.setFont(font);
	plusOneScore.setString("+1 Score");
	plusOneScore.setCharacterSize(30);
	plusOneScore.setFillColor(Color(0, 102, 0));
	//plusOneScore.setStyle(Text::Bold);
	plusOneScore.setOutlineColor(Color(0, 50, 0));
	plusOneScore.setOutlineThickness(4);
	textRect = plusOneScore.getGlobalBounds();
	plusOneScore.setOrigin(Vector2f(textRect.width / 2.0f, textRect.height));
	plusOneScore.setPosition(-100, -100);
	
	// ---------- SHAPES ----------
	CircleShape tempCircle(25, 8);
	tempCircle.setFillColor(Color(0, 102, 0, 126));
	tempCircle.setOutlineThickness(4);
	tempCircle.setOutlineColor(Color(0, 50, 0, 126));
	tempCircle.setOrigin(Vector2f(25, 25));
	centerPosition.x = 400;
	centerPosition.y = 400;
	tempCircle.setPosition(centerPosition.x, centerPosition.y);
	center = tempCircle;

	// ---------- CHOOSING WHICH SHAPE TO SPAWN FIRST ----------
	RectObject tempRect;
	TriangleObject tempTriangle;
	CircleObject tempCircleObj;
	int choose = rand() % 3;
	switch (choose) {
		case 0:
			numberOfRectObjects = 1;
			tempRect.init(100);
			for (int i = 0; i < numberOfRectObjects; i++) {
				rectangleObjects[i] = tempRect;
			}
			break;
		case 1:
			numberOfTriangleObjects = 1;
			tempTriangle.init(15);
			for (int i = 0; i < numberOfTriangleObjects; i++) {
				triangleObjects[i] = tempTriangle;
			}
			break;
		case 2:
			numberOfCircleObjects = 1;
			tempCircleObj.init(12);
			for (int i = 0; i < numberOfCircleObjects; i++) {
				circleObjects[i] = tempCircleObj;
			}
			break;
	}

	// ---------- HEALTH BAR ----------
	RectangleShape tempBar(Vector2f(300, 24));
	tempBar.setOrigin(Vector2f(150, 24));
	tempBar.setOutlineThickness(4);
	tempBar.setOutlineColor(Color(0, 50, 0));
	tempBar.setPosition(600, 788);

	healthbarBack = tempBar;
	healthbarBack.setFillColor(Color(0, 50, 0));

	healthbarFront = tempBar;
	healthbarFront.setFillColor(Color(0, 102, 0));

	// ---------- POWER UPS ----------
	extraHealth.init(Color(0, 0, 102, 255), Color(0, 0, 50, 255));
	/*extraHealth.position.x = 236;
	extraHealth.position.y = 200;*/
	invulnerability.init(Color(154, 77, 0, 255), Color(50, 25, 0, 255));
	/*invulnerability.position.x = 200;
	invulnerability.position.y = 200;*/
}

void Game::update(RenderWindow &window, GameOver &gameOver) {
	//int tempInt;

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		gameState = 0;
	}

	time(&timeNow);
	
	// ---------- SPAWNING NEW OBJECTS EVERY 10 SECONDS ----------
	dif = difftime(timeNow, timeLast);
	if ((dif >= 10)) {
		bool hitMax[] = { numberOfRectObjects == MAX_RECT, numberOfTriangleObjects == MAX_TRIANGLE, numberOfCircleObjects == MAX_CIRCLE };
		/*if (numberOfRectObjects == MAX_RECT) {
			hitMax[0] = true;
		}
		if (numberOfTriangleObjects == MAX_TRIANGLE) {
			hitMax[1] = true;
		}*/
		
		int choose = rand() % 3;
		RectObject tempRect;
		TriangleObject tempTriangle;
		CircleObject tempCircle;

		if (hitMax[0]) {
			if (hitMax[1]) {
				choose = 2;
			}
			else if (hitMax[2]) {
				choose = 1;
			}
			else {
				choose = rand() % 2 + 1;
			}
		}
		else if (hitMax[1]) {
			if (hitMax[0]) {
				choose = 2;
			}
			else if (hitMax[2]) {
				choose = 0;
			}
			else {
				choose = (rand() % 1) * 2;
			}
		}
		else if (hitMax[2]) {
			if (hitMax[0]) {
				choose = 1;
			}
			else if (hitMax[1]) {
				choose = 0;
			}
			else {
				choose = rand() % 2;
			}
		}
		
		switch (choose) {
			case 0:
				if (numberOfRectObjects < MAX_RECT) {
					numberOfRectObjects++;
					tempRect.init(100);
					rectangleObjects[numberOfRectObjects - 1] = tempRect;
				}
				break;
			case 1:
				if (numberOfTriangleObjects < MAX_TRIANGLE) {
					numberOfTriangleObjects++;
					tempTriangle.init(15);
					triangleObjects[numberOfTriangleObjects - 1] = tempTriangle;
				}
				break;
			case 2:
				if (numberOfCircleObjects < MAX_CIRCLE) {
					numberOfCircleObjects++;
					tempCircle.init(12);
					circleObjects[numberOfCircleObjects - 1] = tempCircle;
				}
				break;
		}


		for (int i = 0; i < numberOfRectObjects; i++) {
			rectangleObjects[i].speed += 0.1;
		}

		for (int i = 0; i < numberOfTriangleObjects; i++) {
			triangleObjects[i].speed += 0.1;
		}

		for (int i = 0; i < numberOfCircleObjects; i++) {
			circleObjects[i].speed += 0.1;
		}

		time(&timeLast);
	}

	// ---------- SPAWNING A POWERUP EVERY 15 SECONDS ----------
	dif = difftime(timeNow, timeLast2);
	if (dif >= 15) {
		// ---------- ENSURE THAT THE POWERUP CHOSEN IS DIFFERENT EACH TIME ----------
		int choose = rand() % (plusHealthBias + invulnerabilityBias);
		if (choose < plusHealthBias) {
			extraHealth.generate();
			invulnerabilityBias++;
		}
		else {
			invulnerability.generate();
			plusHealthBias++;
		}
		
		time(&timeLast2);
	}
	
	// ---------- 5 SECONDS OF INVULNERABILITY ----------
	dif = difftime(timeNow, timeLast3);
	if (dif >= 5) {
		vulnerable = true;
		vulnerableTimeLeft = 0;
	}

	if (!vulnerable) {
		vulnerableTimeLeft = dif;
	}

	// ---------- MOVES, ROTATEES AND PULSES OBJECTS ----------
	for (int i = 0; i < numberOfRectObjects; i++) {
		rectangleObjects[i].move(player.playerShape, true);
	}

	for (int i = 0; i < numberOfTriangleObjects; i++) {
		triangleObjects[i].pulse();
		triangleObjects[i].move(player.playerShape, true);
	}

	for (int i = 0; i < numberOfCircleObjects; i++) {
		circleObjects[i].move(player.playerShape, true);
	}

	// ---------- MOVES POWERUPS ----------
	extraHealth.move();
	invulnerability.move();

	player.playerMove(window, centerPosition.x, centerPosition.y); // PLAYER MOVEMENT

	// ---------- SCORE INCREASE EVERY 10 SECONDS ----------
	char tempString[50];

	dif = difftime(timeNow, startTime);
	if (dif >= 10) {
		score++;
		time(&startTime);
	}
	sprintf_s(tempString, "Score: %d", score);
	scoreText.setString(tempString);

	/*char tempString2[50];
	sprintf_s(tempString2, "Health: %d", health);
	healthText.setString(tempString2);*/

	// ---------- MAKES TEXT GO UP BY 1 IN Y AXIS ----------
	plusOne.setPosition(plusOne.getPosition().x, plusOne.getPosition().y - 1);
	minusOne.setPosition(minusOne.getPosition().x, minusOne.getPosition().y - 1);
	plusOneScore.setPosition(plusOneScore.getPosition().x, plusOneScore.getPosition().y - 1);

	// ---------- CHECKS FOR COLLISION ----------
	for (int i = 0; i < numberOfRectObjects; i++) {
		if (rectangleObjects[i].checkForCollision(player.playerShape)) {
			if (!vulnerable) {
				score++;
				plusOneScore.setPosition(400, 400);
				healthGetPosition.y = 400;
			}
			else {
				health--;
				minusOne.setPosition(400, 400);
				healthGetPosition.y = 400;
			}
		}
	}

	for (int i = 0; i < numberOfCircleObjects; i++) {
		if (circleObjects[i].checkForCollision(player.playerShape)) {
			if (!vulnerable) {
				score++;
				plusOneScore.setPosition(400, 400);
				healthGetPosition.y = 400;
			}
			else {
				health--;
				minusOne.setPosition(400, 400);
				healthGetPosition.y = 400;
			}
		}
	}
	for (int i = 0; i < numberOfTriangleObjects; i++) {
		if (triangleObjects[i].checkForCollision(player.playerShape)) {
			if (!vulnerable) {
				score++;
				plusOneScore.setPosition(400, 400);
				healthGetPosition.y = 400;
			}
			else {
				health--;
				minusOne.setPosition(400, 400);
				healthGetPosition.y = 400;
			}
		}
	}

	// ---------- COLLISION WITH POWERUPS ----------
	if (extraHealth.checkForCollision(player.playerShape)) {
		health++;
		extraHealth.position.x = 900;
		extraHealth.position.y = 900;
		extraHealth.angleOfMovement = 90;

		plusOne.setPosition(400, 400);
		healthGetPosition.y = 400;
	}

	if (invulnerability.checkForCollision(player.playerShape)) {
		vulnerable = false;
		time(&timeLast3);
		invulnerability.position.x = 900;
		invulnerability.position.y = 900;
		invulnerability.angleOfMovement = 90;
	}

	// ---------- MAKES TEXT DISAPPER WHEN IT HAS GONE TO A CERTAIN POSITION AT Y-AXIS ----------
	float tempfloat = healthGetPosition.y - 48.0f;
	if (plusOne.getPosition().y <= tempfloat) {
		plusOne.setPosition(-100, -100);
	}
	if (minusOne.getPosition().y <= tempfloat) {
		minusOne.setPosition(-100, -100);
	}
	if (plusOneScore.getPosition().y <= tempfloat) {
		plusOneScore.setPosition(-100, -100);
	}

	// ---------- HEALTH BAR ONLY GOES UP TO 20, BUT THE PLAYER CAN HAVE 20+ HEALTH ----------
	if (health <= 20) {
		healthbarFront.setSize(Vector2f((health / 20.0f) * 300, 24)); // SET SIZE OF HEALTH BAR
	}

	// ---------- CHECKS IF THE PLAYER HAS LOST ----------
	if (health <= 0) {
		gameState = 3; // GAME OVER

		if (score > highscore) {
			highscore = score;
		}

		gameOver.reset(score, highscore);
	}
}

void Game::draw(RenderWindow &window) {
	window.clear();

	window.draw(gameBackground);

	window.draw(center);

	if (!vulnerable) {
		//window.draw(vulnerableTime);
		arc.draw(400, 400, 44, 0, (360 / 4) * vulnerableTimeLeft, 10, Color(25, 14, 1), window);
		arc.draw(400, 400, 44, 0, (360 / 4) * vulnerableTimeLeft, 6, Color(102, 52, 2), window);
	}

	for (int i = 0; i < numberOfRectObjects; i++) {
		rectangleObjects[i].draw(window);
	}

	for (int i = 0; i < numberOfTriangleObjects; i++) {
		triangleObjects[i].draw(window);
	}

	for (int i = 0; i < numberOfCircleObjects; i++) {
		circleObjects[i].draw(window);
	}

	extraHealth.draw(window);
	invulnerability.draw(window);

	window.draw(player.playerShape);

	window.draw(instructions);
	window.draw(escToExit);
	window.draw(scoreText);

	window.draw(plusOne);
	window.draw(minusOne);
	window.draw(plusOneScore);
	window.draw(healthbarBack);
	window.draw(healthbarFront);

	window.display();
}

void Game::mainLoop(RenderWindow &window, GameOver &gameOver) {

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

	update(window, gameOver);
	draw(window);
}
