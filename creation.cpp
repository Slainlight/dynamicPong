#include <SFML/Graphics.hpp>

extern int wWidth;
extern int wHeight;

extern int pWidth;
extern int pHeight;

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
	sf::CircleShape x(8);
	x.setRadius(5);
	x.setPosition(wWidth / 2, wHeight / 2);
	return x;
}