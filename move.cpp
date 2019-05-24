#include <SFML/Graphics.hpp>
#include "globalVar.h"
#include "func.h"

void eMove(sf::RectangleShape& player, sf::CircleShape following, bool enemy = true)
{
	float fXPos = following.getPosition().x;
	float pXPos = player.getPosition().x;
	float radius = following.getRadius();

	if (enemy)
		player.setPosition(fXPos + radius - pWidth / 2, 0);
	else
		player.setPosition(fXPos + radius - pWidth / 2, wHeight - pHeight);
}

void bMove(sf::CircleShape& ball, float ms, sf::RectangleShape colliders[2])
{
	//static ball vars
	static double speedMod = 0;
	static double ballMod = 0;

	static bool bottomHitLast = false;

	static float speedCap = readVar("speedCap");
	static bool signX = true;
	static bool signY = false;

	//single time use vars
	sf::Vector2f b = ball.getPosition();
	float br = ball.getRadius();

	//checks for collision with sides
	if (b.x + 2 * br > wWidth)
	{
		signX = false;
	}
	else if (b.x < 0)
	{
		signX = true;
	}

	//checks for collision with paddles
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
					ball.setPosition(b.x, pHeight);
				
				if (speedMod < speedCap)
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
					ball.setPosition(b.x, wHeight - (pHeight + br*2));

				if(speedMod < speedCap)
					speedMod += 0.1;
			}
		}
	}

	//updates ball speed and direction
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

	//updates ball movement/size
	ball.move(speed);
	ball.setRadius(readVar("ballRadius") + (ballMod / 2));

	//checks if ball is offscreen, if so reset ball vars
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
	//place holder names
	float xPos = player.getPosition().x;
	float speed = ms/1.6;

	//checks if you can keep moving normally without getting off screen
	if (between(xPos, 0, wWidth - pWidth))
	{
		//changes control scheme to preference
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
		//corrects offscreen movement
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