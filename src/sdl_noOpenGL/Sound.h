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

	void loadSounds();
};

void Sound::loadSounds()
{
	footstep = Mix_LoadWAV("assets/sounds/sand-step.OGG");
	if (footstep == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}