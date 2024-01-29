// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <cstdint>

#include "Bomb.h"

// ---------------------------------------------------------------------------
// main

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
	int const ROW = 30, COLUMN = 53;
	float start_x_axis, start_y_axis, x_axis, y_axis, sqaure_length = 28.f, buffer = 2.f;
	int row_click_index = 0, column_click_index = 0, total_length = sqaure_length + buffer, live_neighbour = 0;
	double total_time{ 0.0 };
	bool pause_state = false;
	s32 mouse_x, mouse_y;
	int display_grid[ROW][COLUMN] = { 0 };
	int ref_grid[ROW][COLUMN] = { 0 };

	// Initialise glider at the start of the game
	display_grid[1][1] = 1; // Cell at (1, 1) alive
	display_grid[2][2] = 1; // Cell at (2, 2) alive
	display_grid[3][0] = 1; // Cell at (3, 0) alive
	display_grid[3][1] = 1; // Cell at (3, 1) alive
	display_grid[3][2] = 1; // Cell at (3, 2) alive

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("GOL !");

	// Loads a font and prepares it at a font height of 72 pixels.
	s8 pFont = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);

	// We inform Alpha Engine that we are going to create a mesh
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x808080FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x808080FF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x808080FF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x808080FF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x808080FF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x808080FF, 0.0f, 0.0f);

	// Saving the mesh in pMesh
	AEGfxVertexList* pMesh = AEGfxMeshEnd();

	// This will load a texture in `Assets/border.png and store it in pTex.
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/border.png");

	// Reset the system modules
	AESysReset();

	// Game Loop
	while (gGameRunning) {
		// Loop start
		AESysFrameStart();

		// Initialise Variables that needs to be reset each loop
		start_x_axis = -777.f;
		start_y_axis = 440.f;
		y_axis = start_y_axis;

		// Get Current time
		total_time += AEFrameRateControllerGetFrameTime();

		// Render grid
		for (int j = 0; j < ROW; ++j) {				// How many Rows
			// Reset x_axis each new ROW
			x_axis = start_x_axis;
			for (int i = 0; i < COLUMN; ++i) {		// How many Columns
				if (display_grid[j][i]) {
					AEMtx33 scale = { 0 };
					AEMtx33Scale(&scale, sqaure_length, sqaure_length);

					AEMtx33 rotate = { 0 };
					AEMtx33Rot(&rotate, 0);

					AEMtx33 translate = { 0 };
					AEMtx33Trans(&translate, x_axis, y_axis);

					AEMtx33 transform_grid = { 0 };
					AEMtx33Concat(&transform_grid, &rotate, &scale);
					AEMtx33Concat(&transform_grid, &translate, &transform_grid);

					AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

					AEGfxSetRenderMode(AE_GFX_RM_COLOR);

					AEGfxSetColorToMultiply(2.0f, 1.0f, 1.0f, 1.0f);

					AEGfxSetColorToAdd(1.0f, 0.0f, 0.0f, 0.0f);
					AEGfxSetBlendMode(AE_GFX_BM_BLEND);
					AEGfxSetTransparency(1.0f);

					AEGfxSetTransform(transform_grid.m);

					AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
				}
				else {
					AEMtx33 scale = { 0 };
					AEMtx33Scale(&scale, sqaure_length, sqaure_length);

					AEMtx33 rotate = { 0 };
					AEMtx33Rot(&rotate, 0);

					AEMtx33 translate = { 0 };
					AEMtx33Trans(&translate, x_axis, y_axis);

					AEMtx33 transform_grid = { 0 };
					AEMtx33Concat(&transform_grid, &rotate, &scale);
					AEMtx33Concat(&transform_grid, &translate, &transform_grid);

					AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
					AEGfxSetRenderMode(AE_GFX_RM_COLOR);

					AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

					AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
					AEGfxSetBlendMode(AE_GFX_BM_BLEND);
					AEGfxSetTransparency(1.0f);

					AEGfxSetTransform(transform_grid.m);

					AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
				}
				// Add length of square + buffer
				x_axis += sqaure_length + buffer;
			}
			// Add length of square + buffer
			y_axis -= sqaure_length + buffer;
		}

		// Puase Button Logic
		if (AEInputCheckTriggered(AEVK_SPACE)) {
			if (!pause_state) {
				pause_state = true;
			}
			else {
				pause_state = false;
			}
		}
		// Pause State
		if (pause_state) {
			// Print Pause text
			AEGfxPrint(pFont,       // font handle given by AEGfxCreateFont()
				"Pause",			// null-terminated c-string to print
				-0.1f,				// x position on normalized coordinates, ranging from -1.f to 1.f
				0.f,				// y position in normalized coordinates, ranging from -1.f to 1.f
				1.f,				// how much to scale the text by
				1.f,				// percentage of red, ranging from 0.f to 1.f
				1.f,				// percentage of green, ranging from 0.f to 1.f
				1.f,				// percentage of blue, ranging from 0.f to 1.f
				1.f);				// percentage of alpha, ranging from 0.f to 1.f

			AEMtx33 scale_border = { 0 };
			AEMtx33Scale(&scale_border, 1600.f, 900.f);

			AEMtx33 rotate = { 0 };
			AEMtx33Rot(&rotate, 0);

			AEMtx33 translate = { 0 };
			AEMtx33Trans(&translate, 0.f, 0.f);

			AEMtx33 transform_border = { 0 };
			AEMtx33Concat(&transform_border, &rotate, &scale_border);
			AEMtx33Concat(&transform_border, &translate, &transform_border);


			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

			// Set the the color to multiply to white, so that the sprite canb display the full range of colors (default is black).
			AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

			// Set the color to add to nothing, so that we don't alter the sprite's color
			AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);

			// Set blend mode to AE_GFX_BM_BLEND, which will allow transparency.
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetTransparency(10.0f);

			// Tell Alpha Engine to use the texture stored in pTex
			AEGfxTextureSet(pTex, 0, 0);

			AEGfxSetTransform(transform_border.m);

			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			// Logic for mouse click
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				AEInputGetCursorPosition(&mouse_x, &mouse_y);
				// Calculate which cell is clicked
				row_click_index = mouse_x / total_length; // Index along the x-axis
				column_click_index = mouse_y / total_length; // Index along the y-axis

				display_grid[column_click_index][row_click_index] = 1;
			}
		}
		// Simulation State
		else {
			// Checking each cell in display array
			for (int j{ 0 }; j < ROW; ++j) {
				for (int i{ 0 }; i < COLUMN; ++i) {
					live_neighbour = 0;
					// Loop to count surrounding horizontal, vertical and diagonal for alive neighbour for each cell
					for (int y{ -1 }; y < 2; ++y) {
						for (int x{ -1 }; x < 2; ++x) {
							// Condition for not out of bound
							if (j + y >= 0 && j + y < ROW && i + x >= 0 && i + x < COLUMN) {
								// Condition to skip cell itself
								if (y != 0 || x != 0) {
									// Incrementing live_neighbour
									if (display_grid[j + y][i + x] == 1) {
										++live_neighbour;
									}
								}
							}
						}
					}
					// After counting total alive neighbour for one cell can proceed to apply Conway's Game of Life rules
					// Any live cell with fewer than two live neighbors dies (emulates underpopulation) 
					// Any live cell with more than three live neighbors dies (emulates overpopulation).
					if (display_grid[j][i] == 1 && (live_neighbour < 2 || live_neighbour > 3)) {
						ref_grid[j][i] = 0;  // Cell dies
					}
					// Any dead cell with exactly three live neighbors becomes a live (emulates reproduction)..
					else if (display_grid[j][i] == 0 && live_neighbour == 3) {
						ref_grid[j][i] = 1;  // Cell becomes alive
					}
					// Any live cell with two or three live neighbors lives on.
					else {
						ref_grid[j][i] = display_grid[j][i];
					}
				}
			}
			if (total_time > 0.1) {
				total_time = 0.0;
				// Copy ref_grid to display_grid
				for (int j = 0; j < ROW; ++j) {
					for (int i = 0; i < COLUMN; ++i) {
						display_grid[j][i] = ref_grid[j][i];
					}
				}

			}
		}

		// call bomb function
		isbomb();

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// This will free the Mesh.
	AEGfxMeshFree(pMesh);

	// 'Frees' the texture.
	AEGfxTextureUnload(pTex);

	// free the system
	AESysExit();
}
