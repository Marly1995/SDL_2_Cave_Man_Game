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
	Mix_Music *theme1 = NULL;
	Mix_Music *theme2 = NULL;
	Mix_Music *theme3 = NULL;
	Mix_Music *theme4 = NULL;
	Mix_Music *theme5 = NULL;
	Mix_Music *theme6 = NULL;

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
	theme1 = Mix_LoadMUS("assets/sounds/theme-1.ogg");
	if (footstep2 == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}