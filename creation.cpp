#include <SFML/Graphics.hpp>
#include "globalVar.h"
#include "func.h"

sf::RectangleShape createPlayer(bool enemy = false)
{
	sf::RectangleShape x;
	int xPos = (wWidth / 2) - (pWidth / 2);
	int yPos = wHeight - pHeight;

	if (enemy)
		yPos = 0;

	x.setPosition(xPos, yPos);
	x.setSize(sf::Vector2f(pWidth, pHeight));
	return x;
}

sf::CircleShape createBall()
{
	sf::CircleShape x(readVar("ballRadius"));
	x.setPosition(wWidth / 2, wHeight / 2);
	return x;
}