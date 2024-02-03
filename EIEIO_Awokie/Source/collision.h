#pragma once

#include "enum.h"
#include "Initialisation.h"
#include <iostream>
int collisionResult(int objectId, int objectId2);
int collide(int stationaryId, int movingId, int xVelo, int yVelo, int xPos2, int yPos2, int result);

