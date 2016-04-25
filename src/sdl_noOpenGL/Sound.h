#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_mixer.h>

using namespace std;

class Sound
{
private:

public:
	Mix_Chunk *footstep = NULL;
	Mix_Chunk *footstep2 = NULL;

	void loadSounds();
};

void Sound::loadSounds()
{
	footstep = Mix_LoadWAV("assets/sounds/wood-1.wav");
	if (footstep == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	footstep2 = Mix_LoadWAV("assets/sounds/wood-3.wav");
	if (footstep2 == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}