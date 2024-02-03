// definition for function isbomb

#include <crtdbg.h> // To check for memory leaks
#include "Bomb.h"

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
bool bombstate{0};

f32 xaxis = -((PLAY_AREA_WIDTH + CEll_HEIGHT + CEll_BUF) / 2);
f32 yaxis = ((PLAY_AREA_HEIGHT - 100 + CEll_HEIGHT + CEll_BUF) / 2);


void isbomb(AEGfxVertexList* pMesh, AEGfxTexture* pTex, AEMtx33 transform[][SIZE_COL]) {

	// testing only to be deleted------------------------
	//bomb_array[bombstate][2][2] = 1;
	//bomb_array[bombstate][1][1] = 1;
	//bomb_array[bombstate][8][2] = 1;
	//bomb_array[bombstate][4][4] = 1;
	//bomb_array[bombstate][7][7] = 1;
	// testing code ends here-----------------------------


	// Create a scale matrix that scales by 500 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, CEll_HEIGHT, CEll_HEIGHT);

	// Create a translation matrix that translates by
	// 200 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, xaxis, yaxis);

	AEMtx33 transform2[SIZE_ROW][SIZE_COL] = { 0 };

	// if mouse click
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&pX, &pY);

		index_col = pX / (CEll_HEIGHT + CEll_BUF);
		index_row = (pY - CEll_HEIGHT / 1.2) / (CEll_HEIGHT + CEll_BUF);
		bomb_array[bombstate][index_row][index_col] = !bomb_array[bombstate][index_row][index_col];
	}


	for (int i = 0; i < SIZE_ROW; i++) {
		for (int j = 0; j < SIZE_COL; j++) {


			if (bomb_array[bombstate][i][j] == 1) {

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

				AEMtx33Concat(&transform2[i][j], &translate, &scale);

				AEGfxSetTransform(transform[i][j].m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

				
			}

		}
	}


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



