#pragma once

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

struct allcollision {
	position finalposition ();
	velocity movevelocity ();
	int collisionresult = 0;

};

int collisionResult(int objectId, int objectId2);

allcollision collide(int stationaryId, int movingId, int xVelo, int yVelo, int xPos2, int yPos2, int result, allcollision);

