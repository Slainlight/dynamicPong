#pragma once
#include <SFML/Graphics.hpp>
#include "globalVar.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

bool between(float num, float min, float max);
void events(sf::RenderWindow& window);
void twoPlayerChange(bool& twoPlayers);
int readVar(string name);