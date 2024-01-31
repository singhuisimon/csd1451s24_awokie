// definition for function isbomb

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "Bomb.h"
#include "Initialisation.h"

// initialising
// bomb state
int bomb = 0;
// mouse
s32 pX = 0;
s32 pY = 0;

// bomb array
int index_row = 0;
int index_col = 0;
bool bomb_array[2][SIZE_ROW][SIZE_COL]{ 0 };
bool bombstate{};



void isbomb() {

	// load font of 100px
	//s8 pFont = AEGfxCreateFont("Assets/liberation-mono.ttf", 100);

	// create a mesh
	// rmb remove the mesh cuz its looping
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh
	AEGfxVertexList* pMesh = AEGfxMeshEnd();

	// load texture
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/bomb01.png");

	

	// scale
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, CEll_HEIGHT * 1.5f, CEll_HEIGHT * 1.5f);

	// create a rotation matrix
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	// create a translation matrix
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, 0 - (PLAY_AREA_WIDTH / 2), 0);


	// concatenate the matrices into the 'transform' variable.
	// transform for bomb
	AEMtx33 transform2 = { 0 };
	transform2 = {0};
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
	AEMtx33Concat(&transform2, &translate, &scale);

	// tell Alpha Engine to use the matrix in 'transform' to apply onto all
	// the vertices of the mesh that we are about to choose to draw in the next line.
	AEGfxSetTransform(transform2.m);


	// if mouse click
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&pX, &pY);
		index_col = pX / (CEll_HEIGHT + CEll_BUF);
		index_row = pY / (CEll_HEIGHT + CEll_BUF);
		bomb_array[bombstate][index_row][index_col] = !bomb_array[bombstate][index_row][index_col];
	}

	// draw bomb in the grid
	for (int i = 0; i < SIZE_ROW; ++i) {
		for (int j = 0; j < SIZE_COL; ++j) {
			if (bomb_array[bombstate][i][j] == 1) {

				// draw the bomb
				//codes here that I havnt put
		
				// tell the Alpha Engine to get ready to draw something with texture.
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

				// add color
				AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

				// set blend mode to AE_GFX_BM_BLEND, which will allow transparency.
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetTransparency(1.0f);

				// tell Alpha Engine to use the texture stored in pTex
				AEGfxTextureSet(pTex, 0, 0);

				AEMtx33Trans(&translate, i, j);
				AEMtx33 transform2 = { 0 };
				AEMtx33Concat(&transform2, &translate, &scale);


				// code the things here


				// tell Alpha Engine to use the matrix in 'transform' to apply onto all
				// the vertices of the mesh that we are about to choose to draw in the next line.
				AEGfxSetTransform(transform2.m);

				// tell Alpha Engine to draw the mesh with the above settings.
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
			}
		}
	}


	

	

	// free the texture
	AEGfxTextureUnload(pTex);
}





// have an array of bomb

/*
const int numberOfBombs = 5; // You can change this to the desired size

// Create an array of Bomb objects
Bomb bombs[numberOfBombs];

// Access and use the Bomb objects in the array
for (int i = 0; i < numberOfBombs; ++i) {
	std::cout << "Detonating bomb #" << i + 1 << ": ";
	bombs[i].explode();
}

return 0;
*/


// float totaltime{};
// totaltime = getdt
// if bomb drop
// if getdt > 2.0f {
// totaltime = 0;
//blablabla
//}



