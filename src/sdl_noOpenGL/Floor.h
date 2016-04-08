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

class Floor
{
public:
	GameObject obj;

	Floor();
	Floor(int xPosition, int yPosition);
};

Floor::Floor() {
	obj.xPos = NULL;
	obj.yPos = NULL;
	obj.width = NULL;
	obj.height = NULL;
}

Floor::Floor(int xPosition, int yPosition) {
	obj.xPos = xPosition;
	obj.yPos = yPosition;
	obj.width = 32;
	obj.height = 32;
}