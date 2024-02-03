#include "collision.h"
#include <iostream>
//collilde()

//velocity 
//time t of collision
//SET END POSITION OR RETURN IT
//SUGGESTED TO NOT DO THE VELOCITY CHECKS HERE
//struct position {
//	int x;
//	int y;
//}finalPosition2;
//
//struct velocity {
//	int x; //speed and direction of the object, Positive is to the right Negative is to the left
//	int y; //speed and direction of the object, Positive is to the right Negative is to the left
//} moveVelocity2;
//
//struct allCollision {
//	position finalPosition2;
//	velocity moveVelocity2;
//	int collisionResult;
//
//};

allcollision collisionResult(int objectId, int objectId2, allcollision collisionData) {
	switch (objectId) {
		case EMPTY_CELL: {
			//return 
			collisionData.collisionresult = PASS;
			return collisionData; 
		}
		case SOFT_WALL: {
			//return 
			switch (objectId2){
				case PLAYER: {
					//if collision statement
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case WOLF: {
					//if collision statement
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = PASS;
					return collisionData;
					//or stop? //or new variable? 
				}
				case KEY:{
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case EXPLOSION:{
					collisionData.collisionresult = DESTROY;
					return collisionData;
				}
				default: {
					return collisionData;
				}
			}
			break;
		}
		case HARD_WALL: {
			switch (objectId2){
				case PLAYER: {
					//if collision statement
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case WOLF: {
					//if collision statement
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case KEY:{
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case EXPLOSION:{
					//return PASS;
					//or 
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				default: {
					return collisionData;
				}
			}
			break;
		}
		case DISINTEGRATING_WALL: {
			switch (objectId2){
				case PLAYER: {
					//if collision statement
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case WOLF: {
					//if collision statement
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case KEY:{
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case EXPLOSION:{
					//return DESTROY;
					//or 
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				default: {
					return collisionData;
				}
			}
			break;
		}
		
		case PLAYER: {
			switch (objectId2) {
			case DOOR: {
				//if collision statement
				//if no key 
				collisionData.collisionresult = STOP;
				return collisionData;
				// else if key and sheep
				//return pass
				//else return win code 4
			}
			case WOLF: {
				//if collision statement
				collisionData.collisionresult = STOP;
				return collisionData;
			}
			case SHEEP: {
				collisionData.collisionresult = STOP;
				return collisionData;
			}
			case KEY: {
				collisionData.collisionresult = STOP;
				return collisionData;
			}
			case BOMB: {
				collisionData.collisionresult = STOP;
				return collisionData;
			}
			case EXPLOSION: {
				//return DESTROY;
				//or 
				collisionData.collisionresult = STOP;
				return collisionData;
			}
			default: {
				return collisionData;
			}
			}
			break;
		}
		case WOLF: {
			switch (objectId2) {
				case DOOR: {
					//if collision statement
					//if no key 
					collisionData.collisionresult = STOP;
					return collisionData;
					// else if key and sheep
					//return pass
					//else return win code 4
				}
				case PLAYER: {
					//if collision statement
					collisionData.collisionresult = DESTROY;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = DESTROY;
					return collisionData;
				}
				case KEY: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = STOP;
					return collisionData; //can return new result - run if needed for AI
				}
				case EXPLOSION: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
			}
			break;
		}

		case SHEEP: {
			switch (objectId2) {
				case SOFT_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case DISINTEGRATING_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case EMPTY_CELL: {
					collisionData.collisionresult = PASS;
					return collisionData;

				}
				case HARD_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case DOOR: {
					//if collision statement
					//if no key
					collisionData.collisionresult = STOP;
					return collisionData;
					// else if key and sheep
					//return pass
					//else return win code 4
				}
				case PLAYER: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case KEY: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = STOP;
					return collisionData; //can return new result - run if needed for AI
				}
				case EXPLOSION: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				default: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
			}
			break;
		}
		case KEY: {
			switch (objectId2) {
				case SOFT_WALL: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case DISINTEGRATING_WALL: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case EMPTY_CELL: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case HARD_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case DOOR: {
					//if collision statement
					//if no key 
					collisionData.collisionresult = STOP;
					return collisionData;
					// else if key and sheep
					//return pass
					//else return win code 4
				}
				case PLAYER: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case EXPLOSION: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				default: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
			}
			break;
		}
		case BOMB: {
			switch (objectId2) {
				case SOFT_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case DISINTEGRATING_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case EMPTY_CELL: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case HARD_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case DOOR: {
					//if collision statement
					//if no key 
					collisionData.collisionresult = STOP;
					return collisionData;
					// else if key and sheep
					//return pass
					//else return win code 4
				}
				case PLAYER: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case EXPLOSION: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case WOLF: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				default: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
			}
			break;
		}
		case EXPLOSION: {
			switch (objectId2) {
				case SOFT_WALL: {
					collisionData.collisionresult = DESTROY;
					return collisionData;
				}
				case DISINTEGRATING_WALL: {
					collisionData.collisionresult = DESTROY;
					return collisionData;
				}
				case EMPTY_CELL: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case HARD_WALL: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case DOOR: {
					//if collision statement
					//if no key 
					collisionData.collisionresult = STOP;
					return collisionData;
					// else if key and sheep
					//return pass
					//else return win code 4
				}
				case PLAYER: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case SHEEP: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
				case BOMB: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case EXPLOSION: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				case WOLF: {
					collisionData.collisionresult = STOP;
					return collisionData;
				}
				default: {
					collisionData.collisionresult = PASS;
					return collisionData;
				}
			}
			break;
		}
		default: {

			std::cout << "TEST 4" << std::endl;
			break;
		}
			
	}
	return collisionData;
}

// Check if there is collision within the same frame.
allcollision collide(int stationaryId, int movingId, PlayerStruct player, int result, allcollision collisionData) {
	if (result == STOP) {
		std::cout << "STOP" << std::endl;
		collisionData.collisionresult = PASS;
		return collisionData;
	}
	else if (result == PASS) {
		std::cout << "PASS" << std::endl;
		collisionData.collisionresult = PASS;
		return collisionData;
	}
	else if (result == DESTROY) {
		std::cout << "DESTROY" << std::endl;
		collisionData.collisionresult = DESTROY;
		return collisionData;
	}
	return collisionData;
}
//btw 2 squares;
//find min dist
//dFirst = a.min.x - b.max.x;
////find max dist
//dLast = a.max.x - b.min.x; 


//derilative velocity (VRel.x)


// Both axis should always be colliding\
// Take max btw the 2 first times
// Take min btw the 2 last times

