#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "sprite.h"
#include "GameObject.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class Enemy 
{
public:
	
	GameObject obj;

	int yStartingPosition = 0;
	int xStartingPosition = 0;

	int pathStage = 0;

	int xEnemySpriteIndex = 0;
	int yEnemySpriteIndex = 0;

	int xEnemyIdleSpriteIndex[6] = { 0, 80, 160, 240, 320, 400 };
	int yEnemyIdleSpriteIndex[6] = { 0, 0, 0, 0, 0, 0 };
	int xEnemyWalkSpriteIndex[8] = { 0, 80, 80, 80, 80 };
	int yEnemyWalkSpriteIndex[8] = { 62, 62, 62, 62, 62 };
	int xEnemyClimbSpriteIndex[4] = { 160, 240 };
	int yEnemyClimbSpriteIndex[4] = { 124, 124 };

	void enemyMove();
	void enemyPath();
};

void Enemy::enemyMove()
{
	if (pathStage == 0)
	{
		obj.xPos += 2;
	}
	if (pathStage == 1)
	{
		obj.yPos += 2;
	}
}

void Enemy::enemyPath()
{
	if (pathStage == 0 &&
		obj.xPos >= 256)
	{
		pathStage = 1;
	}
	if (pathStage == 1 &&
		obj.yPos >= 160)
	{
		pathStage = 2;
	}
}