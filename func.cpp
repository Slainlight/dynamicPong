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

void twoPlayerChange(bool& twoPlayers)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		twoPlayers = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		twoPlayers = false;
	}
}

int readVar(string wantedName)
{
	string line;
	ifstream input("settings.txt");

	while (getline(input, line))
	{
		istringstream ss(line);
		string name;
		int var;

		ss >> name >> var;

		if (wantedName == name)
		{
			return var;
		}
	}

	string defaultNames[] = {"windowWidth", "windowHeight", "paddleWidth", "paddleHeight", "ctrlScheme", "fpsMax", "ballRadius", "speedCap", "twoPlayer", "auto"};
	int defaultValues[] =   {         1280,            720,           150,             10,            0,      120,            5,          2,           0,      0};

	//defaults if nothing else was found
	for (int i = 0; i < defaultNames->length() + 1; i++)
	{
		if (defaultNames[i] == wantedName)
		{
			return defaultValues[i];
		}
	}
}
