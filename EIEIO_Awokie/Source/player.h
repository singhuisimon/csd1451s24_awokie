#pragma once

#include "AEEngine.h"
#include "Initialisation.h"
#include "enum.h"

void player(AEGfxVertexList* pMesh, AEGfxTexture* pTex, AEMtx33 transform_player);

struct PlayerStruct {
	int id = PLAYER;
	/*float x;
	float y;*/
	float x = 100.f;
	float y = -175.f;
<<<<<<< HEAD
=======
	float veloX = 0;
	float veloY = 0;
>>>>>>> main
};
PlayerStruct playermovement();