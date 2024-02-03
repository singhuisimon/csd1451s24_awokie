#pragma once
enum objectId {
	EMPTY_CELL = 0,						// 0 Empty cell - Green Grass so that the user passes through. 
	SOFT_WALL,							// 1 Soft Wall - cannot be passed through but can be destroyed.
	HARD_WALL,							// 2 Hard Wall - cannot pass through, cannot be destroyed
	DISINTEGRATING_WALL,				// 3 Disappearing Wall - cannot pass through unless the wall is destroyed or destroys itself
	PLAYER,								// 4 Player - cannot pass through above, can pass through bomb, cannot pass through Wolves
	WOLF,								// 5 Wolves - cannot pass through walls or player
	SHEEP,								// 6 Sheep - Spawns in a destructable wall, collected when colliding with player or wolves
	KEY,								// 7 Key - Spawns in a destructable wall, collected only when colliding with player.
	BOMB,								// 8 Bomb - User can pass through this, wolf cannot, sheep cannot.
	EXPLOSION,							// 9 Explode Area - None can pass through this except Empty Cell, Hard Wall, Key, Bomb and Door. 
										//					All others are destroyed if hit. Player loses a life.
	DOOR								// 10 Door - User collides with this holding the key to complete the level.
};

enum collisionResult{
	PASS = 0,							// 0 Pass through empty cells or explosion passes through undestructable walls
	STOP,								// 1 Do not move. Or when explosion stops when hitting undestructable walls. 
	DESTROY,							// 2 Destroy when the bomb explosion hit the destructable wall.
										// 2 Destroy also used when enemy or bomb hits the sheep.
	COLLECT								// 3 destroy and collect might be the same. Collect for key and sheeps
};

struct Cell {
	objectId state;
	//float disintegrationTimers[SIZE_ROW][SIZE_COL];
};