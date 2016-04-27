#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "sprite.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class Enemy 
{
public:
	int enemySpeed = 0;
	int enemyHealth = 20;
	int enemyMove = 0;
	double enemyDecide = 0;

	int xEnemy = 100;
	int yEnemy = 100;

	int xEnemySpriteIndex = 0;
	int yEnemySpriteIndex = 0;
};