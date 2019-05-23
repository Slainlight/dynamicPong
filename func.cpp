#include "func.h"

void events(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}
	}
}

bool between(float num, float min, float max)
{
	if (num >= min && num <= max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool twoPlayerChange()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		return true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		return false;
	}
}
