#pragma once

//struct
struct Player {
	AEGfxTexture* pTexPlayer;
	AEGfxVertexList* pMeshPlayer;
};

void player(Player*);
void freePlayer(Player*);
void playermovement();