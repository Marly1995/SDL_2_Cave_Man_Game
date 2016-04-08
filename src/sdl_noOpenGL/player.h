#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "GameObject.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class player
{
public:

	GameObject obj;

	float hSpeed;
	float vSpeed;
	float vMove;
	int damage = 0;
	int playerHealth = 50;
	float jumpTime = 0.0f;

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
	int gravity;

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

	void playerLimits();
};

enum class CollisionType { allPoints, bothtop, bothleft, bothright, bothbottom, botLeft, none };
CollisionType tmpCollisionType = CollisionType::none;

void player::playerLimits()
{
	/*if (obj.botSide == true) {
		gravity = 0;
		moveUp = false;
		moveDown = false;
	}
	// all player points collide
	if (obj.botLeft == true &&
		obj.botRight == true &&
		obj.topLeft == true &&
		obj.topRight == true) {
		tmpCollisionType = CollisionType::allPoints;
	}
	// both bottom points collide
	else if (obj.botLeft == true &&
		obj.botRight == true) {
		tmpCollisionType = CollisionType::bothbottom;
	}
	// both top points collide
	else if (obj.topLeft == true &&
		obj.topRight == true) {
		tmpCollisionType = CollisionType::bothtop;
	}
	// both left points collide
	 else if (obj.topLeft == true &&
		obj.botLeft == true) {
		 tmpCollisionType = CollisionType::bothleft;
	}
	// both right points collide
	else if (obj.topRight == true &&
		obj.botRight == true){
		tmpCollisionType = CollisionType::bothright;
	}
	// bottom left point collides
	else if (obj.botLeft == true) {
		tmpCollisionType = CollisionType::botLeft;
	}

	switch (tmpCollisionType)
	{
	case CollisionType::allPoints:
		break;
	case CollisionType::bothtop:
		moveDown = false;
		moveUp = false;
		break;
	case CollisionType::bothleft:
		break;
	case CollisionType::bothright:
		break;
	case CollisionType::bothbottom:
		moveDown = false;
		moveUp = false;
		gravity = 0;
		break;
	case CollisionType::botLeft:
		break;
	default:
		break;
	}*/
}