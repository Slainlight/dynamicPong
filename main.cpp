#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

using namespace std;

int wWidth = 1280;
int wHeight = 720;

int pWidth = 150;
int pHeight = 5;

bool between(float num, float min, float max);
void events(sf::RenderWindow& window);

void pMove(sf::RectangleShape& player, float ms, int controlType = 0);
void eMove(sf::RectangleShape& player, sf::CircleShape following, bool enemy = true);
void bMove(sf::CircleShape& ball, float ms, sf::RectangleShape colliders[2]);

sf::RectangleShape createPlayer(bool enemy = false);
sf::CircleShape createBall();

int main()
{
	sf::Clock deltaClock;

	//window var
	const static string wName = "Pong";
	constexpr int fpsMax = 300;

	//window
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), wName);
	window.setFramerateLimit(fpsMax);

	//game Objs
	sf::RectangleShape player = createPlayer();
	sf::RectangleShape enemy = createPlayer(true);
	sf::CircleShape ball = createBall();
	
	sf::View view;
	view.setSize(sf::Vector2f(1280, 720));
	view.setCenter(wWidth / 2, wHeight / 2);
	
	int zoom = 1;

	while (window.isOpen())
	{
		float ms = float(deltaClock.restart().asMilliseconds());
		events(window);

		//move
		eMove(enemy, ball);
		//eMove(player, ball, 0);
		pMove(player, ms, 1);

		sf::RectangleShape players[2] = { player, enemy };
		bMove(ball, ms, players);

		//printf("%d\n", int(ms));

		//draw
		window.clear();

		window.draw(player);
		window.draw(enemy);
		window.draw(ball);
		
		window.display();
	}

	return 0;
}