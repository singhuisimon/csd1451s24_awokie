#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "AI.h"

// Initialise wolf position bottom right
f32 AI_x_axis = 750.f, AI_y_axis = -375.f;

void check_available_index() {

}

void move_ai() {


}

void draw_ai(AEGfxVertexList* pMesh, AEGfxTexture* pTex) {
	// Size
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, CEll_HEIGHT, CEll_HEIGHT);
	
	// Rotation
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	// Position
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, AI_x_axis, AI_y_axis);

	// Combine
	AEMtx33 transform_wolf = { 0 };
	AEMtx33Concat(&transform_wolf, &rotate, &scale);
	AEMtx33Concat(&transform_wolf, &translate, &transform_wolf);

	// Tell the Alpha Engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Set the the color to multiply to white, so that the sprite can
	// display the full range of colors (default is black).
	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	// set blend mode to AE_GFX_BM_BLEND, which will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	// Tell Alpha Engine to use the texture stored in pTex
	AEGfxTextureSet(pTex, 0, 0);

	// Tell Alpha Engine to use the matrix in 'transform' to apply onto all
	// the vertices of the mesh that we are about to choose to draw in the next line.
	AEGfxSetTransform(transform_wolf.m);

	// Tell Alpha Engine to draw the mesh with the above settings.
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}