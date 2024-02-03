// -------------------------- LIBRARY DEFINITIONS ----------------------------
#include <iostream>
#include <stdlib.h>   
#include <time.h>
#include <crtdbg.h> // To check for memory leaks


// ------------------------ HEADER FILE DEFINITIONS --------------------------
#include "AEEngine.h"
#include "Structures.h"
#include "Bomb.h"
#include "Initialisation.h"
#include "Render.h"
#include "enum.h"
#include "collision.h"
#include "player.h"
// ---------------------------------------------------------------------------


// without texture, multiple sprite, keypress, pause state

// ---------------------------------------------------------------------------
// main

//#define SIZE_BUF 2
//#define REN_BUF 0
//#define UPD_BUF 1

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

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, PLAY_AREA_WIDTH, PLAY_AREA_HEIGHT, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("EIEIO");

	// reset the system modules
	AESysReset();
	PlayerStruct player2;
	allcollision collision;

	f32 xaxis = -((PLAY_AREA_WIDTH + CEll_HEIGHT + CEll_BUF) / 2);
	f32 yaxis = ((PLAY_AREA_HEIGHT - 100 + CEll_HEIGHT + CEll_BUF) / 2);
	Cell array[SIZE_ROW][SIZE_COL] = {};

	for (int i = 0; i < SIZE_ROW; i++) {
		for (int j = 0; j < SIZE_COL; j++) {
			array[i][j].state = EMPTY_CELL;
		}
	}

	//  top bottom boundary hardwalls
	for (int i = 0; i < SIZE_ROW; i++) {
		for (int j = 0; j < SIZE_COL; j++) {
			if (i == 0 || i == (SIZE_ROW - 1)) {
				array[i][j].state = HARD_WALL;
			}
		}
	}

	// left boundary hardwalls
	for (int i = 1; i < SIZE_ROW - 1; i++) {
		for (int j = 0; j < SIZE_COL; j++) {
			if (j == 0 || j == (SIZE_COL - 1)) {
				array[i][j].state = HARD_WALL;
			}
		}
	}

	// alternating hardwalls
	for (int i = 1; i < SIZE_ROW - 2; i++) {
		for (int j = 1; j < SIZE_COL - 2; j++) {
			if (i % 2 == 0 && j % 2 == 0) {
				array[i][j].state = HARD_WALL;
			}
			else {
				array[i][j].state = EMPTY_CELL;
			}
		}
	}

	// generating the softwalls aka brown tiles
	srand(static_cast<unsigned int> (time(NULL)));
	for (int i = 1; i < SIZE_ROW - 1; i++) {
		for (int j = 1; j < SIZE_COL - 1; j++) {
			if (array[i][j].state != HARD_WALL) {
				if (int randcount = rand() % 2) {
					array[i][j].state = SOFT_WALL;
				}
			}
		}

	}

	for (int i = 1; i < SIZE_ROW - 1; i++) {
		for (int j = 1; j < SIZE_COL - 1; j++) {
			if (array[i][j].state == SOFT_WALL) {
				int randcount2 = rand() % 2;
				if (randcount2 == 0) {
					array[i][j].state = DISINTEGRATING_WALL;
				}
				else {
					array[i][j].state = SOFT_WALL;
				}

			}
		}

	}

	float disintegrationTimers[SIZE_ROW][SIZE_COL]={};
	// Initialize the disintegration timers
	for (int i = 0; i < SIZE_ROW; i++) {
		for (int j = 0; j < SIZE_COL; j++) {
			disintegrationTimers[i][j] = 0.0f;
		}
	}






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

	// Load the Texture of the fixed tiles
	AEGfxTexture* pFixedTiles = AEGfxTextureLoad("Assets/fixed-tiles.png");
	AEGfxTexture* pBreakables = AEGfxTextureLoad("Assets/Breakables.png");
	AEGfxTexture* pGrass = AEGfxTextureLoad("Assets/grass.png");
	AEGfxTexture* pPlayerTex = AEGfxTextureLoad("Assets/farmer3d.png");


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
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
				AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetTransparency(1.0f);
				if (array[i][j].state == HARD_WALL) {
					
					
					AEGfxTextureSet(pFixedTiles, 0, 0);
					//AEGfxSetColorToAdd(-0.56f, -0.56f, -0.56f, 0.0f); //grey

				}
				else if (array[i][j].state == EMPTY_CELL) {
					
					AEGfxTextureSet(pGrass, 0, 0);

					//AEGfxSetColorToAdd(-0.74f, -0.44f, -0.96f, 0.0f); //green

				}
				else if (array[i][j].state == SOFT_WALL) {

					AEGfxTextureSet(pBreakables, 0, 0);
					//AEGfxSetColorToAdd(-0.27f, -0.48f, -0.78f, 0.0f);//#B87333 brown


				}
				else if (array[i][j].state == DISINTEGRATING_WALL) {

					AEGfxTextureSet(pBreakables, 0, 0);
					//AEGfxSetColorToAdd(-0.33f, -0.44f, -0.20f, 0.0f);//lilac
				}

				//draw_hardwall(pMesh, pPlayerTex, transform[i][j]);
				AEGfxSetTransform(transform[i][j].m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			}
		}

		// call bomb function
		isbomb(pMesh, pBombTex, transform, array);

		bool previousDisintegrated{ true };
		// Update the disintegration process
		for (int i = 1; i < SIZE_ROW - 1; i++) {
			for (int j = 1; j < SIZE_COL - 1; j++) {

				// Inside the loop
				if (array[i][j].state == DISINTEGRATING_WALL) {
					if (previousDisintegrated == true) {
						disintegrationTimers[i][j] += static_cast<float> (AEFrameRateControllerGetFrameTime());
						printf("Timer[%d][%d]: %f\n", i, j, disintegrationTimers[i][j]);  // Debugging output
						if (disintegrationTimers[i][j] > 3.0f) {
							array[i][j].state = EMPTY_CELL;
							printf("Cell[%d][%d] Disintegrated!\n", i, j);  // Debugging output
							disintegrationTimers[i][j] = 0.0f;
						}

					}
					previousDisintegrated = (array[i][j].state == EMPTY_CELL);

				}


				/*if (array[i][j].state == DISINTEGRATING_WALL) {
					// Check if the previous cell was a disintegrating cell that has turned into an empty cell
					bool previousDisintegrated = (array[i - 1][j].state == !DISINTEGRATING_WALL);

					// If the previous cell has disintegrated, proceed with the current cell
					if (previousDisintegrated) {
						array[i][j].disintegrationTimer += AEFrameRateControllerGetFrameTime();


						if (array[i - 1][j].disintegrationTimer > 20.0f) {
							array[i][j].state = EMPTY_CELL;
							printf("Timer[%d][%d]: %f\n", i, j, disintegrationTimers[i][j]);
							array[i - 1][j].disintegrationTimer = 0.0f;
							printf("Cell[%d][%d] Disintegrated!\n", i, j);  // Debugging output
						}
					}
				}*/


			}
		}
		player(pMesh, pPlayerTex, transform_player, player2);
		player2 = playermovement(collision.collisionresult, player2);
		//find array position from the player position
		//arrayNum 
		//std::cout << player2.x <<std::endl;

		// find the array value
		//call collision function
		//int result = collisionResult(HARD_WALL, PLAYER);

		//int currentXGrid = (int)(player2.x / (CEll_HEIGHT+ CEll_BUF));
		//int currentYGrid = (int)(PLAY_AREA_HEIGHT - player2.y) / (CEll_HEIGHT + CEll_BUF);
		//int nextXGrid = (int)(player2.veloX / (CEll_HEIGHT + CEll_BUF));
		//int nextYGrid = (int)(PLAY_AREA_HEIGHT -  player2.veloY) / (CEll_HEIGHT + CEll_BUF);

		int currentXGrid = static_cast<int>((player2.x + PLAY_AREA_WIDTH/2) / (CEll_HEIGHT + CEll_BUF));
		std::cout << "Player2 X" << (player2.x + PLAY_AREA_WIDTH / 2) << std::endl;
		std::cout << "current X" << currentXGrid << std::endl;
		int currentYGrid = static_cast<int>((-player2.y + PLAY_AREA_HEIGHT/2) / (CEll_HEIGHT + CEll_BUF));
		std::cout << "current Y" << currentYGrid << std::endl << std::endl;
		int nextXGrid = static_cast<int>((player2.veloX + PLAY_AREA_WIDTH/2) / (CEll_HEIGHT + CEll_BUF));
		std::cout << "next X" << nextXGrid << std::endl;
		int nextYGrid = static_cast<int>((-player2.veloY + PLAY_AREA_HEIGHT/2) / (CEll_HEIGHT + CEll_BUF));
		std::cout << "next Y" << nextYGrid << std::endl;
		// find the array value
		

		//call collision function
		collision = collisionResult(array[nextXGrid][nextYGrid].state, PLAYER, collision);
		collision = collide(array[nextXGrid][nextYGrid].state, PLAYER, player2, collision.collisionresult, collision);
		
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pPlayerTex);
	//AEGfxDestroyFont(pFont);


	// free the system
	AESysExit();
}
