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
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int yStartingPosition = 0;
	int xStartingPosition = 0;

	int pathStage = 0;

	int xEnemySpriteIndex = 0;
	int yEnemySpriteIndex = 0;

	int walk = 0;
	int climb = 0;

	//int xEnemyIdleSpriteIndex[6] = { 0, 80, 160, 240, 320, 400 };
	//int yEnemyIdleSpriteIndex[6] = { 0, 0, 0, 0, 0, 0 };
	int xEnemyWalkSpriteIndex[7] = { 0, 80, 160, 240, 320, 240, 160 };
	int yEnemyWalkSpriteIndex[7] = { 62, 62, 62, 62, 62, 62, 62 };
	int xEnemyClimbSpriteIndex[2] = { 160, 240 };
	int yEnemyClimbSpriteIndex[2] = { 124, 124 };

	void enemyMove();
	void enemyPath();

	void enemyMove1();
	void enemyPath1();
};

void Enemy::enemyMove()
{
	if (pathStage == 0)
	{
		obj.xPos += 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_NONE;
	}
	if (pathStage == 1)
	{
		obj.yPos += 2;
		xEnemySpriteIndex = xEnemyClimbSpriteIndex[climb];
		yEnemySpriteIndex = yEnemyClimbSpriteIndex[climb];
	}
	if (pathStage == 2)
	{
		obj.xPos -= 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (pathStage == 3)
	{
		obj.xPos += 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_NONE;
	}
	if (pathStage == 4)
	{
		obj.yPos -= 2;
		xEnemySpriteIndex = xEnemyClimbSpriteIndex[climb];
		yEnemySpriteIndex = yEnemyClimbSpriteIndex[climb];
	}
	if (pathStage == 5)
	{
		obj.xPos -= 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_HORIZONTAL;
	}
}

void Enemy::enemyPath()
{
	if (pathStage == 0 &&
		obj.xPos >= 224)
	{
		pathStage = 1;
	}
	if (pathStage == 1 &&
		obj.yPos >= 128)
	{
		pathStage = 2;
	}
	if (pathStage == 2 &&
		obj.xPos <= 96)
	{
		pathStage = 3;
	}
	if (pathStage == 3 &&
		obj.xPos >= 224)
	{
		pathStage = 4;
	}
	if (pathStage == 4 &&
		obj.yPos <= 0)
	{
		pathStage = 5;
	}
	if (pathStage == 5 &&
		obj.xPos <= 160)
	{
		pathStage = 0;
	}
}

void Enemy::enemyMove1()
{
	if (pathStage == 0)
	{
		obj.xPos += 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_NONE;
	}
	if (pathStage == 1)
	{
		obj.yPos += 2;
		xEnemySpriteIndex = xEnemyClimbSpriteIndex[climb];
		yEnemySpriteIndex = yEnemyClimbSpriteIndex[climb];
	}
	if (pathStage == 2)
	{
		obj.xPos -= 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (pathStage == 3)
	{
		obj.xPos += 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_NONE;
	}
	if (pathStage == 4)
	{
		obj.yPos -= 2;
		xEnemySpriteIndex = xEnemyClimbSpriteIndex[climb];
		yEnemySpriteIndex = yEnemyClimbSpriteIndex[climb];
	}
	if (pathStage == 5)
	{
		obj.xPos -= 2;
		xEnemySpriteIndex = xEnemyWalkSpriteIndex[walk];
		yEnemySpriteIndex = yEnemyWalkSpriteIndex[walk];
		flip = SDL_FLIP_HORIZONTAL;
	}
}

void Enemy::enemyPath1()
{
	if (pathStage == 0 &&
		obj.xPos >= 224)
	{
		pathStage = 1;
	}
	if (pathStage == 1 &&
		obj.yPos >= 128)
	{
		pathStage = 2;
	}
	if (pathStage == 2 &&
		obj.xPos <= 96)
	{
		pathStage = 3;
	}
	if (pathStage == 3 &&
		obj.xPos >= 224)
	{
		pathStage = 4;
	}
	if (pathStage == 4 &&
		obj.yPos <= 0)
	{
		pathStage = 5;
	}
	if (pathStage == 5 &&
		obj.xPos <= 160)
	{
		pathStage = 0;
	}
}