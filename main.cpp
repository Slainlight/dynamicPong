#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "creation.h"
#include "move.h"

using namespace std;

//personally I prefer AD, but most use arrow keys so that's what it's set to
enum ctrls { AD, LR };

//gameplay vars
constexpr bool ctrlScheme = LR;
constexpr bool twoPlayer = true;

//window var
int wWidth = 1280;
int wHeight = 720;
constexpr int fpsMax = 300;
const static string wName = "Pong";

//game object var
int pWidth = 150;
int pHeight = 5;

int main()
{
	//window
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), wName);
	window.setFramerateLimit(fpsMax);

	//game Objs
	sf::RectangleShape player = createPlayer();
	sf::RectangleShape enemy = createPlayer(true);
	sf::CircleShape ball = createBall();
	sf::Clock deltaClock;

	while (window.isOpen())
	{
		float ms = float(deltaClock.restart().asMilliseconds());
		events(window);

		//move
		sf::RectangleShape players[2] = { player, enemy };
		if (twoPlayer)
		{
			pMove(player, ms, ctrlScheme);
			pMove(enemy, ms, !ctrlScheme);
			bMove(ball, ms, players);
		}
		else
		{
			eMove(enemy, ball);
			pMove(player, ms, ctrlScheme);
			bMove(ball, ms, players);
		}

		//draw
		window.clear();
		window.draw(player);
		window.draw(enemy);
		window.draw(ball);
		window.display();
	}

	return 0;
}