#pragma once

//#include "Structures.h"
#include "enum.h"
#include "Initialisation.h"
#include <iostream>

struct position {
	float x;
	float y;
};

struct velocity {
	float x; //speed and direction of the object, positive is to the right negative is to the left
	float y; //speed and direction of the object, positive is to the right negative is to the left
};


struct AABB {
	position min = {};
	position max = {};
};

struct allcollision {
	position finalposition = {};
	velocity movevelocity = {};
	int collisionresult = 0;
};

struct PlayerStruct {
	int id = PLAYER;
	/*float x;
	float y;*/
	float x = 100.f;
	float y = 220.f;
	AABB ab = { {x - CEll_HEIGHT / 2, y - CEll_HEIGHT / 2}, {x + CEll_HEIGHT / 2, y + CEll_HEIGHT / 2} };
	float veloX = 0;
	float veloY = 0;
};

allcollision collisionResult(int objectId, int objectId2, allcollision collison);

allcollision collide(int stationaryId, int movingId, PlayerStruct player, int result, allcollision);

