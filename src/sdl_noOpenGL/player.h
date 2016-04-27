#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "GameObject.h"
#include "sprite.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class player
{
public:

	GameObject obj;
	Sprite spr;

	float hSpeed;
	float vSpeed;
	float vMove;
	int damage = 0;
	int playerHealth = 50;
	float jumpTime = 0.0f;
	string animation;

	int xPlayerSpriteIndex = 0;
	int yPlayerSpriteIndex = 0;

	bool canClimb;
	bool canFall;
	bool moveCtrl;
	bool climbCtrl;
	bool jumpCtrl;
	bool hitCtrl;

	int playerWalk = 0;
	int playerClimb = 0;
	int playerIdle = 0;
	int playerFall = 0;
	int playerJump = 0;
	int gravity;
	int yStartingPosition = 0;
	int xStartingPosition = 0;

	bool moveDown;
	bool moveUp;
	bool moveLeft;
	bool moveRight;

	bool walkLeft;
	bool walkRight;
	bool climbUp;
	bool climbDown;

	int xPlayerIdleSpriteIndex[6] = { 0, 97, 194, 291, 388, 485 };
	int yPlayerIdleSpriteIndex[6] = { 0, 0, 0, 0, 0, 0 };
	int xPlayerWalkSpriteIndex[8] = { 0, 97, 194, 291, 388, 485, 0, 97 };
	int yPlayerWalkSpriteIndex[8] = { 73, 73, 73, 73, 73, 73, 146, 146 };
	int xPlayerClimbSpriteIndex[4] = { 0, 97, 194, 291 };
	int yPlayerClimbSpriteIndex[4] = { 438, 438, 438, 438 };
	int xPlayerJumpSpriteIndex[3] = { 194, 291, 388 };
	int yPlayerJumpSpriteIndex[3] = { 146, 146, 146 };
	int xPlayerFallSpriteIndex[3] = { 485, 0, 97 };
	int yPlayerFallSpriteIndex[3] = { 146, 219, 219 };

};
