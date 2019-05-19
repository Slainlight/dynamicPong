#include <SFML/Graphics.hpp>

bool between(float num, float min, float max);

extern int wWidth;
extern int wHeight;

extern int pWidth;
extern int pHeight;

void eMove(sf::RectangleShape& player, sf::CircleShape following, bool enemy = true)
{
	if(enemy)
		player.setPosition(following.getPosition().x + following.getRadius() - pWidth / 2, 0);
	else
		player.setPosition(following.getPosition().x + following.getRadius() - pWidth / 2, wHeight-pHeight);
}

void bMove(sf::CircleShape& ball, float ms, sf::RectangleShape colliders[2])
{
	static double speedMod = 0;
	static double ballMod = 0;

	static bool bottomHitLast = false;

	static bool signX = true;
	static bool signY = false;

	sf::Vector2f b = ball.getPosition();
	float br = ball.getRadius();

	if (b.x + 2 * br > wWidth)
	{
		signX = false;
	}
	else if (b.x < 0)
	{
		signX = true;
	}

	for (int i = 0; i < 2; i++)
	{
		sf::Vector2f c = colliders[i].getPosition();

		if (b.y < pHeight)
		{
			if (between(b.x + br, c.x, (c.x + pWidth)) && i == 1)
			{
				signY = true;

				if(bottomHitLast)
					bottomHitLast = false;
					ballMod += 1;
				
				if (speedMod < 2)
					speedMod += 0.1;
			}
		}

		if (b.y + 2 * br > wHeight - pHeight)
		{
			if (between(b.x + br, c.x, (c.x + pWidth)) && i == 0)
			{
				signY = false;

				if (!bottomHitLast)
					bottomHitLast = true;
					ballMod += 1;

				if(speedMod < 2)
					speedMod += 0.1;
			}
		}
	}

	float regSpeed = +ms / (4 - speedMod);
	sf::Vector2f speed;
	if (signX)
	{
		speed.x = +regSpeed;
	}
	else
	{
		speed.x = -regSpeed;
	}

	if (signY)
	{
		speed.y = +regSpeed;
	}
	else
	{
		speed.y = -regSpeed;
	}

	ball.move(speed);
	ball.setRadius(5 + (ballMod / 2));

	if (b.y < -40 || b.y > wHeight + 40)
	{
		ball.setPosition(wWidth / 2, wHeight / 2);
		signX = true;
		signY = false;

		ballMod = 0;
		speedMod = 0;
	}
}


void pMove(sf::RectangleShape& player, float ms, int controlType = 0)
{
	float xPos = player.getPosition().x;
	float speed = ms;

	if (between(xPos, 0, wWidth - pWidth))
	{
		if (controlType == 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.move(-speed, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.move(speed, 0);
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player.move(-speed, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player.move(speed, 0);
			}
		}
	}
	else
	{
		if (xPos > pWidth / 2)
		{
			player.move(-2, 0);
		}
		else
		{
			player.move(2, 0);
		}
	}
}