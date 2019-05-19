#pragma once
#include <SFML/Graphics.hpp>
#include "globalVar.h"

sf::RectangleShape createPlayer(bool enemy = false);
sf::CircleShape createBall();