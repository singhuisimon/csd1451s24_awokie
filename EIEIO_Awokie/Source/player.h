#pragma once

#include "AEEngine.h"
#include "Initialisation.h"
#include "enum.h"
#include "collision.h"


void player(AEGfxVertexList* pMesh, AEGfxTexture* pTex, AEMtx33 transform_player, PlayerStruct player2);

PlayerStruct playermovement(int collided, PlayerStruct player2);