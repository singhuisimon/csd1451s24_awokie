#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "enum.h"
#include "Render.h"

void draw_hardwall(AEGfxVertexList* pMesh, AEGfxTexture* pTex, AEMtx33 transform[SIZE_ROW][SIZE_COL])
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


	AEMtx33Concat(&transform[SIZE_ROW][SIZE_COL], &rotate, &scale);

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

	AEGfxSetTransform(transform[SIZE_ROW][SIZE_COL].m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}