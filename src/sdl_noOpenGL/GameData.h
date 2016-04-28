#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include "GameObject.h"
#include "sprite.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class GameData
{
public:
	int currentScore = 0;
	int highScore = 0;
	int scoreWidth = 32;
	string score;
	int eggCount = 0;

	void convertScore();
};

void GameData::convertScore()
{
	score = static_cast<ostringstream*>(&(ostringstream() << currentScore))->str();
	if (currentScore > 0) { scoreWidth = 64; }
	if (currentScore > 99) { scoreWidth = 96; }
	if (currentScore > 999) { scoreWidth = 128; }
}

