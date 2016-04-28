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

class Egg
{
public:
	GameObject obj;
	
	Egg();
	~Egg();
	Egg(int xPosition, int yPosition);
};

Egg::Egg() {
	obj.xPos = NULL;
	obj.yPos = NULL;
	obj.width = NULL;
	obj.height = NULL;
}

Egg::Egg(int xPosition, int yPosition) {
	obj.xPos = xPosition;
	obj.yPos = yPosition;
	obj.width = 32;
	obj.height = 32;
}

Egg::~Egg()
{

}