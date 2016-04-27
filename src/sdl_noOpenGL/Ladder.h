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

class Ladder
{
public:
	GameObject obj;
	Sprite spr;

	Ladder();
	Ladder(int xPosition, int yPosition);
};

Ladder::Ladder() {
	obj.xPos = NULL;
	obj.yPos = NULL;
}

Ladder::Ladder(int xPosition, int yPosition) {
	obj.xPos = xPosition;
	obj.yPos = yPosition;
	obj.width = 34;
	obj.height = 32;
}