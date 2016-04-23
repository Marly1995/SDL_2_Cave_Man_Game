#pragma once
#include "player.h"
#include "sprite.h"
#include "Level.h"
#include "Enemy.h"
#include "Floor.h"
#include "Ladder.h"
#include "Text.h"
#include "Sound.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_Renderer *ren; //pointer to the SDL_Renderer
SDL_Surface *surface; //pointer to the SDL_Surface
SDL_Texture *playerTex; //pointer to the SDL_Texture
SDL_Texture *floorTex;
SDL_Texture *ladderTex;
SDL_Texture *forestTex;

SDL_RendererFlip playerFlip = SDL_FLIP_NONE;

player Player = player();
Level level = Level();
Enemy enemy = Enemy();
Text text = Text();
Sound sound = Sound();
Floor floorArray[144];
Ladder ladderArray[144];

bool done = false;
bool collisionFrame = false;
bool pause = false;

int animTime = 0;

int x;

bool handleCollision()
{
	//Player.moveDown = true;
	//Player.moveUp = true;
	for (int i = 0; i < 144; i++) {
		if (Player.obj.collisionCheck(floorArray[i].obj) == true) {
			return true;
		}
	}
	return false;

}

bool handleLadderCollision()
{
	//Player.moveDown = true;
	//Player.moveUp = true;
	for (int i = 0; i < 144; i++) {
		if (Player.obj.insideCollisionCheck(ladderArray[i].obj) == true) {
			return true;
		}
	}
	return false;

}

void handleInput()
{
	//Event-based input handling
	//The underlying OS is event-based, so **each** key-up or key-down (for example)
	//generates an event.
	//  - https://wiki.libsdl.org/SDL_PollEvent
	//In some scenarios we want to catch **ALL** the events, not just to present state
	//  - for instance, if taking keyboard input the user might key-down two keys during a frame
	//    - we want to catch based, and know the order
	//  - or the user might key-down and key-up the same within a frame, and we still want something to happen (e.g. jump)
	//  - the alternative is to Poll the current state with SDL_GetKeyboardState

	SDL_Event event; //somewhere to store an event

	//NOTE: there may be multiple events per frame
	while (SDL_PollEvent(&event)) //loop until SDL_PollEvent returns 0 (meaning no more events)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			done = true; //set donecreate remote branch flag if SDL wants to quit (i.e. if the OS has triggered a close event,
							//  - such as window close, or SIGINT
			break;

			//keydown handling - we should to the opposite on key-up for direction controls (generally)
		case SDL_KEYDOWN:
			//Keydown can fire repeatable if key-repeat is on.
			//  - the repeat flag is set on the keyboard event, if this is a repeat event
			//  - in our case, we're going to ignore repeat events
			//  - https://wiki.libsdl.org/SDL_KeyboardEvent
			
			if (!event.key.repeat)
				switch (event.key.keysym.sym)
				{
					//Player.hitCtrl escape to exit
					case SDLK_ESCAPE: done = true;
						break;
					case SDLK_w: if (handleLadderCollision()) {
						Player.moveUp = true;
						Player.climbCtrl = true;
					}
						break;
					case SDLK_s: if (handleLadderCollision()) {
						Player.moveDown = true;
						Player.climbCtrl = true;
					}
						break;
					case SDLK_a:
						playerFlip = SDL_FLIP_HORIZONTAL;
						Player.moveLeft = true;
						Player.moveCtrl = true;
						break;
					case SDLK_d:
						playerFlip = SDL_FLIP_NONE;
						Player.moveRight = true;
						Player.moveCtrl = true;
						break;
					case SDLK_SPACE: Player.jumpCtrl = true;
						Player.jumpTime = 0;
						break;
					case SDLK_p: if (pause == false) { pause = true; }
								 else { pause = false; }
						break;
				}
			break;
		case SDL_KEYUP:
			event.key.repeat = true;
			if (event.key.repeat)
				switch (event.key.keysym.sym)
				{
				case SDLK_w: Player.climbCtrl = false;
					Player.moveUp = false;
					Player.playerWalk = 0;
					break;
				case SDLK_s: Player.climbCtrl = false;
					Player.moveDown = false;
					Player.playerWalk = 0;
					break;
				case SDLK_a: Player.moveCtrl = false;
					Player.moveLeft = false;
					Player.playerWalk = 0;
					break;
				case SDLK_d: Player.moveCtrl = false;
					Player.moveRight = false;
					Player.playerWalk = 0;
				}
			break;
		}
	}
}
void simulateAnimation()
{
	if (animTime >= 3) {

		Player.playerIdle += 1;
		if (Player.playerIdle > 6) {
			Player.playerIdle = 0;
		}
		Player.playerFall += 1;
		if (Player.playerFall > 2) {
			Player.playerFall = 0;
		}
		Player.playerJump += 1;
		if (Player.playerJump > 2) {
			Player.playerJump = 0;
		}
		Player.playerWalk += 1;
		if (Player.playerWalk > 7) {
			Player.playerWalk = 0;
			Mix_PlayChannel(1, sound.footstep, 0);
		}

		if (Player.climbCtrl == true)
		{
			Player.playerClimb += 1;
			if (Player.playerClimb > 3) {
				Player.playerClimb = 0;
			}
		}
		animTime = 0;
	}
}

void handleAnimation()
{
	if (Player.moveCtrl == false) {
		Player.xPlayerSpriteIndex = 0;
	}
	if (Player.climbCtrl == false) {
		Player.xPlayerSpriteIndex = 0;
	}

	if (Player.moveCtrl == true) {
		Player.animation = "walk";
	}
	if (Player.moveCtrl == false) {
		Player.animation = "idle";
	}
	if (Player.climbCtrl == true &&
		handleLadderCollision()) {
		Player.animation = "climb";
	}	
	if (Player.vSpeed < 0 &&
		!handleLadderCollision() &&
		collisionFrame == false) {
		Player.animation = "jump";
	}
	if (Player.vSpeed > 0 &&
		!handleLadderCollision() &&
		collisionFrame == false) {
		Player.animation = "fall";
	}
}

void updateAnimation()
{
	if (Player.animation == "walk")
	{
		Player.xPlayerSpriteIndex = Player.xPlayerWalkSpriteIndex[Player.playerWalk];
		Player.yPlayerSpriteIndex = Player.yPlayerWalkSpriteIndex[Player.playerWalk];
	}
	if (Player.animation == "climb")
	{
		Player.xPlayerSpriteIndex = Player.xPlayerClimbSpriteIndex[Player.playerClimb];
		Player.yPlayerSpriteIndex = Player.yPlayerClimbSpriteIndex[Player.playerClimb];
	}
	if (Player.animation == "idle")
	{
		Player.xPlayerSpriteIndex = Player.xPlayerIdleSpriteIndex[Player.playerIdle];
		Player.yPlayerSpriteIndex = Player.yPlayerIdleSpriteIndex[Player.playerIdle];
	}
	if (Player.animation == "jump")
	{
		Player.xPlayerSpriteIndex = Player.xPlayerJumpSpriteIndex[Player.playerJump];
		Player.yPlayerSpriteIndex = Player.yPlayerJumpSpriteIndex[Player.playerJump];
	}
	if (Player.animation == "fall")
	{
		Player.xPlayerSpriteIndex = Player.xPlayerFallSpriteIndex[Player.playerFall];
		Player.yPlayerSpriteIndex = Player.yPlayerFallSpriteIndex[Player.playerFall];
	}
}
// end::handleInput[]
void handleForces()
{
	if (Player.hSpeed > 0) {
		Player.hSpeed -= 1;
	}
	if (Player.hSpeed < 0)
	{
		Player.hSpeed += 1;
	}
	if (handleLadderCollision()) {
		Player.jumpCtrl = false;
		if (Player.vSpeed > 0) {
			Player.vSpeed -= 1;
		}
		if (Player.vSpeed < 0)
		{
			Player.vSpeed += 1;
		}
	}
	else {
		Player.vSpeed += 2;
	}
}
void handleMovement()
{	
	if (Player.moveUp == true) {
		Player.vSpeed -= 2;
	}
	if (Player.moveDown == true) {
		Player.vSpeed += 2;
	}
	if (Player.moveLeft == true) {
		Player.hSpeed -= 3;
	}
	if (Player.moveRight == true) {
		Player.hSpeed += 3;
	}

	if (Player.jumpCtrl == true && Player.jumpTime < 2.0f
		&& !handleLadderCollision()) {
		Player.vSpeed -= (3.5 - Player.jumpTime);
		Player.jumpTime += 0.15f;
		if (Player.jumpTime >= 2) {
			Player.jumpCtrl = false;
		}
	}
	

	if (Player.vSpeed >= 2) {
		Player.vSpeed = 2;
	}
	if (Player.jumpCtrl == false &&
		Player.vSpeed <= -2) {
		Player.vSpeed = -2;
	}
	if (Player.hSpeed >= 3) {
		Player.hSpeed = 3;
	}
	if (Player.hSpeed <= -3) {
		Player.hSpeed = -3;
	}	
}

void attemptMovement()
{
	Player.obj.xPos += Player.hSpeed;
	while (handleCollision()) {
		if (Player.hSpeed > 0) {
			Player.obj.xPos -= 1;
		}
		if (Player.hSpeed < 0) {
			Player.obj.xPos += 1;
		}

	}

	Player.obj.yPos += Player.vSpeed;
	while (handleCollision()) {
		if (Player.vSpeed > 0) {
			Player.obj.yPos -= 1;
		}
		if (Player.vSpeed < 0) {
			Player.obj.yPos += 1;
		}
		collisionFrame = true;
	}
}
// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
	animTime++;
	

	if (pause == false) {
		handleMovement();
		handleForces();
		attemptMovement();
	}
	simulateAnimation();
	if (pause == false) {
		handleAnimation();
	}
	updateAnimation();
	collisionFrame = false;
}

void render()
{
		//First clear the renderer
		SDL_RenderClear(ren);
		//Draw the texture
		SDL_Rect srcPlayer;
		SDL_Rect dstPlayer;

		SDL_Rect srcBackground;
		SDL_Rect dstBackground;

		SDL_Rect srcFloor;
		SDL_Rect dstFloor;

		srcPlayer.x = Player.xPlayerSpriteIndex;
		srcPlayer.y = Player.yPlayerSpriteIndex;
		srcPlayer.w = 97;
		srcPlayer.h = 71;

		dstPlayer.x = Player.obj.xPos;
		dstPlayer.y = Player.obj.yPos;
		dstPlayer.w = 42;
		dstPlayer.h = 32;

		srcFloor.x = 0;
		srcFloor.y = 0;
		srcFloor.w = 32;
		srcFloor.h = 32;

		dstFloor.x = 0;
		dstFloor.y = 0;
		dstFloor.w = 32;
		dstFloor.h = 32;

		srcBackground.x = 0;
		srcBackground.y = 0;
		srcBackground.w = 800;
		srcBackground.h = 378;

		dstBackground.x = 0;
		dstBackground.y = 0;
		dstBackground.w = 800;
		dstBackground.h = 378;

		text.textRect.x = 100;
		text.textRect.y = 100;
		text.textRect.w = 240;
		text.textRect.h = 48;


		SDL_RenderCopy(ren, forestTex, &srcBackground, &dstBackground);

		for (int i = 0; i < 12; i++) {
			dstFloor.y = (32 * i);
			for (int p = 0; p < 12; p++) {
				dstFloor.x = (32 * p);
				if (level.world[i][p] == 1) {
					SDL_RenderCopy(ren, floorTex, &srcFloor, &dstFloor);
				}
				if (level.world[i][p] == 2) {
					SDL_RenderCopy(ren, ladderTex, &srcFloor, &dstFloor);
				}
			}
			dstFloor.x = 0;
		}
		SDL_RenderCopyEx(ren, playerTex, &srcPlayer, &dstPlayer, 0, NULL, playerFlip);
		if (pause == true){ SDL_RenderCopy(ren, text.textTex, NULL, &text.textRect); }


		//Update the screen
		SDL_RenderPresent(ren);
}

// based on http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
int main( int argc, char* args[] )
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	std::cout << "SDL initialised OK!\n";
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//create window
	win = SDL_CreateWindow("SDL Hello World!", 100, 100, 1000, 1000, SDL_WINDOW_SHOWN);

	//error handling
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	std::cout << "SDL CreatedWindow OK!\n";

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::string imagePath = "assets/sprites/caverman.png";
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	playerTex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (playerTex == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	imagePath = "assets/sprites/floor.png";
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	floorTex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (floorTex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	imagePath = "assets/sprites/ladder.png";
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	ladderTex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (floorTex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	imagePath = "assets/sprites/forest.png";
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	forestTex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (floorTex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Color White = { 255, 255, 255 };

	int ttfReturn = TTF_Init();
	if (ttfReturn  == -1)
	{
		std::cout << "TTF_Init Failed: " << TTF_GetError() << std::endl;
	}
	sound.loadSounds();
	text.initText();
	text.textSurface = TTF_RenderText_Solid(text.sans, "Paused", White);
	text.textTex = SDL_CreateTextureFromSurface(ren, text.textSurface);
	
	int fCount = 0;
	//int lCount = 0;
	for (int i = 0; i < 12; i++) {
		for (int p = 0; p < 12; p++) {
			if (level.world[i][p] == 1){
				floorArray[fCount] = Floor(32 * p, 32 * i);
			}
			if (level.world[i][p] == 2) {
				ladderArray[fCount] = Ladder((32 * p), (32 * i) - 1);
			}
			fCount++;
		}
	}

	while (!done) //loop until done flag is set)
	{

		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		SDL_Delay(20); // unless vsync is on??
	}


	SDL_DestroyTexture(playerTex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
