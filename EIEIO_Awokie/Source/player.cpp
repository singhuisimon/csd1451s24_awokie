#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "player.h"
#include "enum.h"


//float player_x = 100.f;
//float player_y = -175.f;

PlayerStruct player2;

void player(AEGfxVertexList* pMesh, AEGfxTexture* pTex, AEMtx33 transform_player)
{
	
	// Create a scale matrix that scales by 500 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, CEll_HEIGHT, CEll_HEIGHT);

	// Create a rotation matrix that rotates by 90 degrees
	// Note that PI in radians is 180 degrees.
	// Since 90 degrees is 180/2, 90 degrees in radians is PI/2
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	// Create a translation matrix that translates by
	// 200 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, player2.x, player2.y);


	AEMtx33Concat(&transform_player, &rotate, &scale);
	AEMtx33Concat(&transform_player, &translate, &transform_player);

	// draw the bomb

	// tell the Alpha Engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// add color
	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	// set blend mode to AE_GFX_BM_BLEND, which will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	// tell Alpha Engine to use the texture stored in pTex
	AEGfxTextureSet(pTex, 0, 0);

	AEGfxSetTransform(transform_player.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}



PlayerStruct playermovement()
{
	if (AEInputCheckCurr(AEVK_W))
	{
		player2.y += 5;
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		player2.y -= 5;
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		player2.x += 5;
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		player2.x -= 5;
	}
	return player2;
}

