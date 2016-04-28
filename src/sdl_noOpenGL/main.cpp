#pragma once
#include "player.h"
#include "sprite.h"
#include "Level.h"
#include "Enemy.h"
#include "Floor.h"
#include "Ladder.h"
#include "Text.h"
#include "Sound.h"
#include "TextureControl.h"
#include "Egg.h"
#include "GameData.h"

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

SDL_RendererFlip playerFlip = SDL_FLIP_NONE;

TextureControl texCtrl = TextureControl();
player Player = player();
Level level = Level("assets/sprites/floor.png", "assets/sprites/ladder.png", "assets/sprites/forest.png");
Level level2 = Level("assets/sprites/icefloor.png", "assets/sprites/ladder.png", "assets/sprites/iceback.png");
Level level3 = Level("assets/sprites/floor.png", "assets/sprites/ladder.png", "assets/sprites/forest.png");
Enemy enemy = Enemy();
Enemy enemy2 = Enemy();
GameData gameData = GameData();
Text text = Text();
Text score = Text();
Sound sound = Sound();
Floor floorArray[400];
Ladder ladderArray[400];
Egg eggArray[20];


bool done = false;
bool collisionFrame = false;
bool pause = false;
bool fullscreen = false;

int currentLevel = 0;
int width = 640;
int height = 900;
int fxVolume = 128;
int musicVolume = 128;

float animTime = 0;
float audioTime = 0;
float lastTime = 0;
float currentTime = 0;
float runTime = 0;
float realRunTime = 0;
float jumpTime = 0;

int x;
//TODO add save function
//TODO compartmentalise collision for efficiency 
void updateText()
{
	score.updateText();
	score.textSurface = TTF_RenderText_Solid(score.sans, gameData.score.c_str(), score.White);
	score.textTex = SDL_CreateTextureFromSurface(ren, score.textSurface);
	
}
void createText()
{
	text.textSurface = TTF_RenderText_Solid(text.sans, "paused", text.White);
	text.textTex = SDL_CreateTextureFromSurface(ren, text.textSurface);
	score.textSurface = TTF_RenderText_Solid(score.sans, gameData.score.c_str(), score.White);
	score.textTex = SDL_CreateTextureFromSurface(ren, score.textSurface);
}
void Loading()
{

}
void startMenu()
{

}
bool handleCollision()
{
	//Player.moveDown = true;
	//Player.moveUp = true;
	if (currentLevel == 2) {
		for (int i = 1; i < 400; i++) {
			if (Player.obj.collisionCheck(floorArray[i].obj) == true) {
				return true;
			}
		}
	}
	else {
		for (int i = 0; i < 400; i++) {
			if (Player.obj.collisionCheck(floorArray[i].obj) == true) {
				return true;
			}
		}
	}
	return false;

}
void resetLevel()
{
	for (int i = 0; i < 400; i++)
	{
		floorArray[i].obj.nullify();
		ladderArray[i].obj.nullify();
	}
	for (int i = 0; i < 10; i++)
	{
		eggArray[i].obj.nullify();
	}
}
void generateLevel(Level level)
{
	int fCount = 0;
	int lCount = 0;
	int eggCount = 0;
	if (currentLevel == 0) {
		for (int i = 0; i < 24; i++) {
			for (int p = 0; p < 20; p++) {
				if (level.world[i][p] == 1) {
					floorArray[fCount] = Floor(32 * p, (32 * i) + 96);
					floorArray[fCount].obj.definePosition();
					fCount++;
				}
				if (level.world[i][p] == 2) {
					ladderArray[lCount] = Ladder((32 * p), (32 * i) + 96);
					ladderArray[lCount].obj.definePosition();
					lCount++;
				}
				if (level.world[i][p] == 3) {
					eggArray[eggCount] = Egg((32 * p), (32 * i) + 96);
					eggArray[eggCount].obj.definePosition();
					eggCount++;
				}
			}
		}
		fCount = 0;
		lCount = 0;
		eggCount = 0;
	}
	if (currentLevel == 1) {
		for (int i = 0; i < 24; i++) {
			for (int p = 0; p < 20; p++) {
				if (level.world2[i][p] == 1) {
					floorArray[fCount] = Floor(32 * p, (32 * i) + 96);
					floorArray[fCount].obj.definePosition();
					fCount++;
				}
				if (level.world2[i][p] == 2) {
					ladderArray[lCount] = Ladder((32 * p), (32 * i) + 96);
					ladderArray[lCount].obj.definePosition();
					lCount++;
				}
				if (level.world2[i][p] == 3) {
					eggArray[eggCount] = Egg((32 * p), (32 * i) + 96);
					eggArray[eggCount].obj.definePosition();
					eggCount++;
				}
			}
		}
	}
	if (currentLevel == 2) {
		for (int i = 0; i < 24; i++) {
			for (int p = 0; p < 20; p++) {
				if (level.world3[i][p] == 1) {
					floorArray[fCount] = Floor(32 * p, (32 * i) + 96);
					floorArray[fCount].obj.definePosition();
					fCount++;
				}
				if (level.world3[i][p] == 2) {
					ladderArray[lCount] = Ladder((32 * p), (32 * i) + 96);
					ladderArray[lCount].obj.definePosition();
					lCount++;
				}
				if (level.world3[i][p] == 3) {
					eggArray[eggCount] = Egg((32 * p), (32 * i) + 96);
					eggArray[eggCount].obj.definePosition();
					eggCount++;
				}
			}
		}
		fCount = 0;
		lCount = 0;
		eggCount = 0;
	}
}
void loadSprites(Level level)
{
	texCtrl.player.loadSprite("assets/sprites/caverman.png", ren);
	texCtrl.floor.loadSprite(level.floor, ren);
	texCtrl.ladder.loadSprite(level.ladder, ren);
	texCtrl.background.loadSprite(level.background, ren);
	texCtrl.pauseCover.loadSprite("assets/sprites/pauseCover.png", ren);
	texCtrl.bar.loadSprite("assets/sprites/bars.png", ren);
	texCtrl.enemy.loadSprite("assets/sprites/trex.png", ren);
	texCtrl.egg.loadSprite("assets/sprites/egg.png", ren);
}
void loadLevel()
{
	enemy.obj.xPos = 172;
	enemy.obj.yPos = 224;

	enemy2.obj.xPos = 64;
	enemy2.obj.yPos = 480;

	if (currentLevel == 0)
	{
		loadSprites(level);
		generateLevel(level);
	}
	if (currentLevel == 1)
	{
		resetLevel();
		loadSprites(level2);
		generateLevel(level2);
	}
	if (currentLevel == 2)
	{
		resetLevel();
		loadSprites(level3);
		generateLevel(level3);
	}
}
bool handleEggCollision()
{
	//Player.moveDown = true;
	//Player.moveUp = true;
	for (int i = 0; i < 10; i++) {
		if (Player.obj.collisionCheck(eggArray[i].obj) == true) {			
			eggArray[i].obj.dead = true;
			eggArray[i].obj.definePosition();
			gameData.currentScore += 50;
			gameData.eggCount++;
			if (gameData.eggCount >= 10) {
				currentLevel++;
				loadLevel();
				gameData.eggCount = 0;
			}
			Mix_PlayChannel(2, sound.eat, 0);
			gameData.convertScore();
			updateText();
			return true;
		}
	}
	return false;

}
bool handleLadderCollision()
{
	//Player.moveDown = true;
	//Player.moveUp = true;
	for (int i = 0; i <  400; i++) {
		if (Player.obj.insideCollisionCheck(ladderArray[i].obj) == true) {
			return true;
		}
	}
	return false;

}
// TODO make into inputs calss
void handleInput()
{
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

		case SDL_WINDOWEVENT:
			currentTime = SDL_GetTicks();
			cout << "moved window" << endl;
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
					
				case SDLK_SPACE: if (Player.jumpCtrl == false
					&& !handleLadderCollision()) {
					Player.jumpCtrl = true;
					Player.jumpTime = 0;
					jumpTime = 0;
				}
						break;
					
					case SDLK_p: if (pause == false) { pause = true; }
								 else { pause = false; }
						break;

						//pause menu
						
					case SDLK_f: if (pause == true)
					{
						if (fullscreen == false)
						{
							SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
							fullscreen = true;
						}
						else {
							SDL_SetWindowFullscreen(win, 0);
							fullscreen = false;
						}
					}
							
							break;
					case SDLK_EQUALS: if (pause == true)
					{
						musicVolume += 8;
					}
							break;
						case SDLK_MINUS:if (pause == true)
						{
							musicVolume -= 8;
						}
							break;
						case SDLK_0:if (pause == true)
						{
							fxVolume += 8;
						}
							break;
						case SDLK_9:if (pause == true)
						{
							fxVolume -= 8;
						}
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
// TODO playing animation audio
void simulateAudio()
{
	Mix_VolumeMusic(musicVolume);
	Mix_VolumeChunk(sound.footstep, fxVolume);
	Mix_VolumeChunk(sound.footstep2, fxVolume);
	//if (handleEggCollision){ Mix_PlayChannel(1, sound.eat, 0); }
	if (pause == true){ Mix_PauseMusic(); }
	else { Mix_ResumeMusic(); }
	if (Player.animation == "walk") {
		if(audioTime == 14){ Mix_PlayChannel(1, sound.footstep, 0); }
		if (audioTime >= 28){ Mix_PlayChannel(3, sound.footstep2, 0); 
		audioTime = 0;
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
		}
		if (Player.climbCtrl == true)
		{
			Player.playerClimb += 1;
			if (Player.playerClimb > 3) {
				Player.playerClimb = 0;
			}
		}

		enemy.climb += 1;
		enemy2.climb += 1;
		if (enemy.climb > 1) {
			enemy.climb = 0;
			enemy2.climb = 0;
		}
		enemy.walk += 1;
		enemy2.walk += 1;
		if (enemy.walk > 6) {
			enemy.walk = 0;
			enemy2.walk = 0;
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
		Player.moveUp = false;
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

	if (jumpTime < 10.0f
		&& !handleLadderCollision()) {
		Player.vSpeed -= (3.8 - Player.jumpTime);
		Player.jumpTime += (0.05 * jumpTime);
	}
	else {
	Player.jumpTime = 0;
	}
	

	if (Player.vSpeed >= 2) {
		Player.vSpeed = 2;
	}
	if (Player.jumpCtrl == false &&
		Player.vSpeed <= -2) {
		Player.vSpeed = -2;
	}
	if (handleLadderCollision()
		&& Player.vSpeed <= -2) {
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
	Player.obj.xPos += (Player.hSpeed * (runTime));
	while (handleCollision()) {
		if (Player.hSpeed > 0) {
			Player.obj.xPos -= 1;
		}
		if (Player.hSpeed < 0) {
			Player.obj.xPos += 1;
		}
	}

	Player.obj.yPos += Player.vSpeed * runTime;
	while (handleCollision()) {
		if (Player.vSpeed > 0) {
			Player.obj.yPos -= 1;
			Player.jumpCtrl = false;
				Player.jumpTime = 0;
		}
		if (Player.vSpeed < 0) {
			Player.obj.yPos += 1;
		}
		
		collisionFrame = true;
	}
}
void objectInteraction()
{
	
}
// tag::updateSimulation[]
//TODO add score 
//TODO simulate audio function
//TODO simulate AI
//TODO add multiple levels
void updateSimulation(double smiulationTime = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
	if (currentLevel == 2) {
		floorArray[0].obj.yPos -= 2;
		floorArray[0].obj.definePosition();
		if (floorArray[0].obj.yPos <= 100) {
			floorArray[0].obj.yPos = 900;
		}
		while (Player.obj.collisionCheck(floorArray[0].obj) == true) {
			Player.obj.yPos -= 1;
		}
	}
	
	//animTime++;
	Player.jumpCtrl = true;
	cout << Player.jumpCtrl << endl;
	animTime += (runTime);
	audioTime += runTime;
	jumpTime += runTime;
	
	enemy.enemyMove(runTime);
	enemy.enemyPath();
	enemy2.enemyMove1(runTime);
	enemy2.enemyPath1();
	
	if (pause == false) {
		handleMovement();
		handleForces();
		attemptMovement();
		handleEggCollision();
	}
	simulateAnimation();
	if (pause == false) {
		handleAnimation();
	}
	updateAnimation();
	simulateAudio();
	collisionFrame = false;
}
void render()
{
		//First clear the renderer
		SDL_RenderClear(ren);
		SDL_RenderSetLogicalSize(ren, width, height);
		//Draw the texture
		SDL_Rect srcPlayer;
		SDL_Rect dstPlayer;

		SDL_Rect srcEnemy;
		SDL_Rect dstEnemy;

		SDL_Rect srcEnemy2;
		SDL_Rect dstEnemy2;

		SDL_Rect srcEgg;
		SDL_Rect dstScore;

		SDL_Rect srcBar;
		SDL_Rect dstBar;
		SDL_Rect dstBar2;

		SDL_Rect srcBackground;
		SDL_Rect dstBackground;

		SDL_Rect srcFloor;
		SDL_Rect dstFloor;

		dstScore.x = 50;
		dstScore.y = 20;
		dstScore.w = gameData.scoreWidth;
		dstScore.h = 32;

		srcEgg.x = 0;
		srcEgg.y = 0;
		srcEgg.w = 29;
		srcEgg.h = 22;

		srcPlayer.x = Player.xPlayerSpriteIndex;
		srcPlayer.y = Player.yPlayerSpriteIndex;
		srcPlayer.w = 97;
		srcPlayer.h = 71;

		dstPlayer.x = Player.obj.xPos;
		dstPlayer.y = Player.obj.yPos;
		dstPlayer.w = 42;
		dstPlayer.h = 32;

		srcEnemy.x = enemy.xEnemySpriteIndex;
		srcEnemy.y = enemy.yEnemySpriteIndex;
		srcEnemy.w = 80;
		srcEnemy.h = 62;

		dstEnemy.x = enemy.obj.xPos;
		dstEnemy.y = enemy.obj.yPos;
		dstEnemy.w = 42;
		dstEnemy.h = 32;

		srcEnemy2.x = enemy2.xEnemySpriteIndex;
		srcEnemy2.y = enemy2.yEnemySpriteIndex;
		srcEnemy2.w = 80;
		srcEnemy2.h = 62;

		dstEnemy2.x = enemy2.obj.xPos;
		dstEnemy2.y = enemy2.obj.yPos;
		dstEnemy2.w = 42;
		dstEnemy2.h = 32;

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
		dstBackground.y = 100;
		dstBackground.w = 1800;
		dstBackground.h = 800;

		text.textRect.x = 100;
		text.textRect.y = 100;
		text.textRect.w = 240;
		text.textRect.h = 48;

		srcBar.x = 0;
		srcBar.y = 0;
		srcBar.w = 20;
		srcBar.h = 20;

		dstBar.x = 200;
		dstBar.y = 240;
		dstBar.w = fxVolume;
		dstBar.h = 50;

		dstBar2.x = 200;
		dstBar2.y = 340;
		dstBar2.w = musicVolume;
		dstBar2.h = 50;

		SDL_RenderCopy(ren, texCtrl.background.Tex, &srcBackground, &dstBackground);

		for (int i = 0; i < 400; i++)
		{			
			SDL_RenderCopy(ren, texCtrl.floor.Tex, &srcFloor, &floorArray[i].obj.rect);
			SDL_RenderCopy(ren, texCtrl.ladder.Tex, &srcFloor, &ladderArray[i].obj.rect);
		}
		for (int i = 0; i < 10; i++)
		{
			SDL_RenderCopy(ren, texCtrl.egg.Tex, &srcEgg, &eggArray[i].obj.rect);
		}
		SDL_RenderCopyEx(ren, texCtrl.player.Tex, &srcPlayer, &dstPlayer, 0, NULL, playerFlip);
		SDL_RenderCopyEx(ren, texCtrl.enemy.Tex, &srcEnemy, &dstEnemy, 0, NULL, enemy.flip);
		SDL_RenderCopyEx(ren, texCtrl.enemy.Tex, &srcEnemy2, &dstEnemy2, 0, NULL, enemy2.flip);
		if (pause == true){ 
			SDL_RenderCopy(ren, texCtrl.pauseCover.Tex, NULL, &dstBackground);
			SDL_RenderCopy(ren, text.textTex, NULL, &text.textRect);
			SDL_RenderCopy(ren, texCtrl.bar.Tex, &srcBar, &dstBar);
			SDL_RenderCopy(ren, texCtrl.bar.Tex, &srcBar, &dstBar2);
		}

		SDL_RenderCopy(ren, score.textTex, NULL, &dstScore);

		//Update the screen
		SDL_RenderPresent(ren);
}
//|TODO window resizing
// based on http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
int main( int argc, char* args[] )
{
	gameData.convertScore();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	std::cout << "SDL initialised OK!\n";
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//create window
	win = SDL_CreateWindow("SDL Hello World!", 100, 100, width, height, SDL_WINDOW_RESIZABLE);
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

	int ttfReturn = TTF_Init();
	if (ttfReturn  == -1)
	{
		std::cout << "TTF_Init Failed: " << TTF_GetError() << std::endl;
	}
	sound.loadSounds();
	text.initText();
	score.initText();

	loadLevel();

	
	Mix_PlayMusic(sound.theme1, -1);

	Player.obj.xPos = trunc(level.xStartPos);
	Player.obj.yPos = trunc(level.yStartPos);
	while (!done) //loop until done flag is set)
	{

		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		
		//SDL_Delay(20); // unless vsync is on??
		lastTime = currentTime;
		currentTime = SDL_GetTicks();
		realRunTime = (currentTime - lastTime);
		runTime = (currentTime - lastTime) / 20;
		//cout << runTime << endl;

	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
