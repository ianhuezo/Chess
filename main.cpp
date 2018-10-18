#include <SFML/Graphics.hpp>
#include "NewBoard.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string>
#include "Unit.h"
#include "GameSetup.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define X_OFFSET 200
#define TILE_DIMENSION 45
#define Y_OFFSET 80

int main()
{
	//unsigned int frameRate = 65;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess");
	window.setFramerateLimit(60);
	GameSetup game;
	game.init(&window, X_OFFSET, Y_OFFSET, TILE_DIMENSION);
	game.initUnits();
	clock_t wait;
	wait = clock();
	
	int count = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				game.unitClicked();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				game.unitClicked();
			}
		}

		window.clear(sf::Color(255, 255, 255));
		game.moveUnits();
		game.drawEverything();
		window.display();
	}

	return 0;
}