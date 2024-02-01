#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "Player.h"

void player(Player* player)
{
	// We inform Alpha Engine that we are going to create a mesh
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMeshPlayer
	player->pMeshPlayer = AEGfxMeshEnd();

	// This will load a texture in `Assets/PlanetTexture.png and store it in pTexPlayer.
	player->pTexPlayer = AEGfxTextureLoad("Assets/death01.png");

	// Create a scale matrix that scales by 500 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 120.f, 120.f);

	// Create a rotation matrix that rotates by 90 degrees
	// Note that PI in radians is 180 degrees.
	// Since 90 degrees is 180/2, 90 degrees in radians is PI/2
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	// Create a translation matrix that translates by
	// 200 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, 200.f, 100.f);

	// Concatenate the matrices into the 'transform' variable.
	// We concatenate in the order of translation * rotation * scale
	// i.e. this means we scale, then rotate, then translate.
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	// Tell the Alpha Engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Set the the color to multiply to white, so that the sprite can
	// display the full range of colors (default is black).
	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	// Set blend mode to AE_GFX_BM_BLEND, which will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	// Tell Alpha Engine to use the texture stored in pTex
	AEGfxTextureSet(player->pTexPlayer, 0, 0);

	// Tell Alpha Engine to use the matrix in 'transform' to apply onto all
	// the vertices of the mesh that we are about to choose to draw in the next line.
	AEGfxSetTransform(transform.m);

	// Tell Alpha Engine to draw the mesh with the above settings.
	AEGfxMeshDraw(player->pMeshPlayer, AE_GFX_MDM_TRIANGLES);

}
void freePlayer(Player* play)
{

	AEGfxMeshFree(play->pMeshPlayer);
	AEGfxTextureUnload(play->pTexPlayer);
}

/*
void playermovement()
{

	if (AEInputCheckTriggered(AEVK_W)) //player moving up
	{
		Player player = {};

		// Create a scale matrix that scales by 500 x and y
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 200.f, 200.f);

		// Create a rotation matrix that rotates by 90 degrees
		// Note that PI in radians is 180 degrees.
		// Since 90 degrees is 180/2, 90 degrees in radians is PI/2
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0);

		// Create a translation matrix that translates by
		// 200 in the x-axis and 100 in the y-axis
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, 100.f, 100.f);

		// Concatenate the matrices into the 'transform' variable.
		// We concatenate in the order of translation * rotation * scale
		// i.e. this means we scale, then rotate, then translate.
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);

		// Tell the Alpha Engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		// Set the the color to multiply to white, so that the sprite can
		// display the full range of colors (default is black).
		AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

		// Set blend mode to AE_GFX_BM_BLEND, which will allow transparency.
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		// Tell Alpha Engine to use the texture stored in pTex
		AEGfxTextureSet(player.pTexPlayer, 0, 0);

		// Tell Alpha Engine to use the matrix in 'transform' to apply onto all
		// the vertices of the mesh that we are about to choose to draw in the next line.
		AEGfxSetTransform(transform.m);

		// Tell Alpha Engine to draw the mesh with the above settings.
		AEGfxMeshDraw(player.pMeshPlayer, AE_GFX_MDM_TRIANGLES);

	}
}*/

