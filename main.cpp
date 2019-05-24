#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "creation.h"
#include "move.h"

using namespace std;

//personally I prefer AD, but most use arrow keys so that's what it's set to
enum ctrls { AD, LR };

//gameplay vars
bool ctrlScheme = readVar("ctrlScheme");
bool twoPlayer = readVar("twoPlayer");

//window var
int wWidth = readVar("windowWidth");
int wHeight = readVar("windowHeight");
int fpsMax = readVar("fpsMax");
const static string wName = "Dynamic Pong";

//game object var
int pWidth = readVar("paddleWidth");
int pHeight = readVar("paddleHeight");

#if _DEBUG
int main()
#else
int WinMain()
#endif
{
	//window
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), wName);
	window.setFramerateLimit(fpsMax);

	//game Objs
	sf::RectangleShape player = createPlayer();
	sf::RectangleShape enemy = createPlayer(true);
	sf::CircleShape ball = createBall();
	sf::Clock deltaClock;

	bool automaticPlay = readVar("auto");

	while (window.isOpen())
	{
		float ms = float(deltaClock.restart().asMilliseconds());
		events(window);

		//move
		sf::RectangleShape players[2] = { player, enemy };
		
		twoPlayerChange(twoPlayer);
		if (!automaticPlay)
		{
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
		}
		else
		{
			eMove(enemy, ball);
			eMove(player, ball, 0);
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