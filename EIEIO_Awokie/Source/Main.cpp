

#include <crtdbg.h> // To check for memory leaks
#include "Bomb.h"
#include "Initialisation.h"
#include "player.h"
#include "enum.h"
#include "collision.h"
#include "AEEngine.h"
#include <iostream>



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here
	PlayerStruct player2;
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, PLAY_AREA_WIDTH, PLAY_AREA_HEIGHT, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("EIEIO");

	// reset the system modules
	AESysReset();

	f32 xaxis = -((PLAY_AREA_WIDTH + CEll_HEIGHT + CEll_BUF) /2);
	f32 yaxis = ((PLAY_AREA_HEIGHT-100 + CEll_HEIGHT + CEll_BUF) / 2);
	s8 pFont = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
	int array[SIZE_ROW][SIZE_COL];

		for (int i = 0; i < SIZE_ROW; i++) {
			for (int j = 0; j < SIZE_COL; j++) {
				array[i][j] = EMPTY_CELL; // the green grass
			}
		}
		array[0][0] = SOFT_WALL;

		for (int i = 0; i < SIZE_ROW; i++) {
			for (int j = 0; j < SIZE_COL; j++) {
				if (i == 0 || i == (SIZE_ROW - 1)) {
					array[i][j] = HARD_WALL; // grey stones top and bottom
				}
			}
		}

		for (int i = 1; i < SIZE_ROW-1; i++) {
			for (int j = 0; j < SIZE_COL; j++) {
				if (j == 0 || j == (SIZE_COL - 1)) {
					array[i][j] = HARD_WALL; // grey stones left and right
				}
			}
		}

		for (int i = 1; i < SIZE_ROW-2 ; i++) {
			for (int j = 1; j < SIZE_COL-2 ; j++) {
				if (i % 2 == 0 && j % 2 == 0) {
					array[i][j] = HARD_WALL; //alternating grey stones
				}
				else {
					array[i][j] = EMPTY_CELL;
				}
			} 
		}
		array[1][3] = SOFT_WALL;
		array[2][3] = SOFT_WALL;
		array[3][3] = SOFT_WALL;
		array[3][2] = SOFT_WALL;
		array[3][1] = SOFT_WALL;
		 
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

	// Saving the mesh (list of triangles) in pMesh
	AEGfxVertexList* pMesh = AEGfxMeshEnd();
	//AEGfxTexture* pTex = AEGfxTextureLoad("Assets/fixed-tiles.png");
	AEGfxTexture* pBombTex = AEGfxTextureLoad("Assets/bomb01.png");
	AEGfxTexture* pPlayerTex = AEGfxTextureLoad("Assets/farmer.png");


	// Create a scale matrix that scales by 500 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, CEll_HEIGHT, CEll_HEIGHT);

	// Create a translation matrix that translates by
	// 200 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33 transform[SIZE_ROW][SIZE_COL] = { 0 };
	AEMtx33 transform_player = { 0 };

	
	// create the grids
	for (int i = 0; i < SIZE_ROW; i++) {
		yaxis -= static_cast <f32>(CEll_HEIGHT + CEll_BUF);
		for (int j = 0; j < SIZE_COL; j++)
		{
			xaxis += static_cast<f32>(CEll_HEIGHT + CEll_BUF);
			AEMtx33Trans(&translate, xaxis, yaxis);
			AEMtx33Concat(&transform[i][j], &translate, &scale);

		}
		xaxis = -((PLAY_AREA_WIDTH + CEll_HEIGHT + CEll_BUF) / 2);
	}



	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);

		// Your own rendering logic goes here
		// Tell the Alpha Engine to set the background to black.
		AEGfxSetBackgroundColor(0.40f, 0.53f, 0.25f);


		// Set the color to multiply to white, so that the sprite can
		// display the full range of colors (default is black).
		AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);


		// Tell Alpha Engine to use the matrix in 'transform' to apply onto all
		// the vertices of the mesh that we are about to choose to draw in the next line.
		for (int i = 0; i < SIZE_ROW; i++) {
			for (int j = 0; j < SIZE_COL; j++) {
				if (array[i][j] == HARD_WALL) {
					AEGfxSetColorToAdd(-0.56f, -0.56f, -0.56f, 0.0f); //grey

				}
				else if (array[i][j] == EMPTY_CELL) {
					AEGfxSetColorToAdd(-0.74f, -0.44f, -0.96f, 0.0f); //green

				}
				else if (array[i][j] == SOFT_WALL) {
					AEGfxSetColorToAdd(-0.27f, -0.48f, -0.78f, 0.0f);//#B87333 brown


				}
				AEGfxSetTransform(transform[i][j].m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			}
		}

		// call bomb function
		isbomb(pMesh, pBombTex, transform);

		//call player function
		player(pMesh, pPlayerTex, transform_player);
		player2 = playermovement();
		//find array position from the player position
		//arrayNum 
		std::cout << player2.x <<std::endl;
<<<<<<< HEAD

		// find the array value
		//call collision function
		int result = collisionResult(HARD_WALL, PLAYER);
=======
		int currentXGrid = player2.x / (CEll_HEIGHT+ CEll_BUF);
		int currentYGrid = (PLAY_AREA_HEIGHT - player2.y) / (CEll_HEIGHT + CEll_BUF);
		int nextXGrid = player2.veloX / (CEll_HEIGHT + CEll_BUF);
		int nextYGrid = (PLAY_AREA_HEIGHT - player2.veloY) / (CEll_HEIGHT + CEll_BUF);

		// find the array value
		//call collision function
		int result = collisionResult(array[nextXGrid][nextYGrid], array[currentXGrid][currentYGrid]);
>>>>>>> main
		
		collide(HARD_WALL, PLAYER, 5,6,34,78, result);

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// free everything
	AEGfxMeshFree(pMesh);
	AEGfxDestroyFont(pFont);
	AEGfxTextureUnload(pBombTex);
	AEGfxTextureUnload(pPlayerTex);


	// free the system
	AESysExit();
}
