#pragma once
#include <SFML/Graphics.hpp>
#include "globalVar.h"
#include "func.h"

void pMove(sf::RectangleShape& player, float ms, int controlType = 0);
void eMove(sf::RectangleShape& player, sf::CircleShape following, bool enemy = true);
void bMove(sf::CircleShape& ball, float ms, sf::RectangleShape colliders[2]);