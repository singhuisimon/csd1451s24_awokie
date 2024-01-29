// definition for function isbomb

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "Bomb.h"

// initialising
int bomb = 1;

void isbomb() {

	// load font of 100px
	s8 pFont = AEGfxCreateFont("Assets/liberation-mono.ttf", 100);

	// load texture
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/bomb01.png");

	// key function
	if (AEInputCheckTriggered(AEVK_BACK)) {
		if (bomb == 1) {
			bomb = 0;
		}
		else {
			bomb = 1;
		}
	}

	// if key triggered logic
	if (bomb == 1) {
		// draws text
		

		AEGfxPrint(pFont,       // font handle given by AEGfxCreateFont()
			"Bomb",			// null-terminated c-string to print
			-0.1f,				// x position on normalized coordinates, ranging from -1.f to 1.f
			0.f,				// y position in normalized coordinates, ranging from -1.f to 1.f
			2.f,				// how much to scale the text by
			1.f,				// percentage of red, ranging from 0.f to 1.f
			1.f,				// percentage of green, ranging from 0.f to 1.f
			1.f,				// percentage of blue, ranging from 0.f to 1.f
			1.f);				// percentage of alpha, ranging from 0.f to 1.f

	}

		

		
	


	// free the font
	AEGfxDestroyFont(pFont);

	// free the texture
	AEGfxTextureUnload(pTex);
}





