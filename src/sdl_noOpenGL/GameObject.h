#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>

using namespace std;

class GameObject
{
public:
	SDL_Rect rect;

	float xPos;
	float yPos;
	int width = 32;
	int height = 32;

	int leftSide;
	int rightSide;
	int topSide;
	int botSide;

	bool dead = false;

	void findCollisionPlayer();
	void findCollision();
	bool collisionCheck(GameObject other);
	bool insideCollisionCheck(GameObject other);
	void definePosition();
	void nullify();
};

void GameObject::findCollision()
{
	leftSide = xPos;
	topSide = yPos;
	rightSide = xPos + width;
	botSide = yPos + height;
}

void GameObject::findCollisionPlayer()
{
	leftSide = xPos + 12;
	topSide = yPos + 4;
	rightSide = xPos + width - 4;
	botSide = yPos + height - 4;
}

bool GameObject::collisionCheck(GameObject other)
{
	findCollisionPlayer();
	other.findCollision();

	if (leftSide >= other.rightSide) {
		return false;
	}
	if (rightSide <= other.leftSide) {
		return false;
	}
	if (topSide >= other.botSide) {
		return false;
	}
	if (botSide <= other.topSide) {
		return false;
	}
	return true;
}

bool GameObject::insideCollisionCheck(GameObject other) {
	findCollisionPlayer();
	other.findCollision();

	if (//leftSide <= other.leftSide ||
		leftSide >= other.rightSide) {
		return false;
	}
	if (//rightSide >= other.rightSide ||
		rightSide <= other.leftSide) {
		return false;
	}
	if (botSide <= other.topSide) {
		return false;
	}
	if (topSide >= other.botSide) {
		return false;
	}
	return true;
}

void GameObject::definePosition()
{
	if (dead == true) {
		nullify();
	}
	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height;
}

void GameObject::nullify()
{
	xPos = NULL;
	yPos = NULL;
	width = NULL;
	height = NULL;
	rect.x = NULL;
	rect.y = NULL;
}