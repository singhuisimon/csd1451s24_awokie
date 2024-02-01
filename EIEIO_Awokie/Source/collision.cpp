#include "collision.h"
#include "enum.h"
#include <iostream>
//collilde()

//velocity 
//time t of collision
//SET END POSITION OR RETURN IT
//SUGGESTED TO NOT DO THE VELOCITY CHECKS HERE

int collisionResult(int objectId, int objectId2) {
	switch (objectId) {
		case EMPTY_CELL: {
			//return 
			return PASS; 
		}
		case SOFT_WALL: {
			//return 
			switch (objectId2){
				case PLAYER: {
					//if collision statement
					
					return STOP;
				}
				case WOLF: {
					//if collision statement
					return STOP;
				}
				case SHEEP: {
					return PASS;
					//or stop? //or new variable? 
				}
				case KEY:{
					return PASS;
				}
				case BOMB: {
					return STOP;
				}
				case EXPLOSION:{
					return DESTROY;
				}
				default: {
					return -1;
				}
			}
			break;
		}
		case HARD_WALL: {
			switch (objectId2){
				case PLAYER: {
					//if collision statement
					return STOP;
				}
				case WOLF: {
					//if collision statement
					return STOP;
				}
				case SHEEP: {
					return STOP;
				}
				case KEY:{
					return STOP;
				}
				case BOMB: {
					return STOP;
				}
				case EXPLOSION:{
					return PASS;
					//or 
					return STOP;
				}
				default: {
					return -1;
				}
			}
			break;
		}
		case DISINTEGRATING_WALL: {
			switch (objectId2){
				case PLAYER: {
					//if collision statement
					return STOP;
				}
				case WOLF: {
					//if collision statement
					return STOP;
				}
				case SHEEP: {
					return STOP;
				}
				case KEY:{
					return STOP;
				}
				case BOMB: {
					return STOP;
				}
				case EXPLOSION:{
					return DESTROY;
					//or 
					return STOP;
				}
				default: {
					return -1;
				}
			}
			break;
		}
		
		case PLAYER: {
			switch (objectId2) {
			case DOOR: {
				//if collision statement
				//if no key 
				return STOP;
				// else if key and sheep
				//return pass
				//else return win code 4
			}
			case WOLF: {
				//if collision statement
				return STOP;
			}
			case SHEEP: {
				return STOP;
			}
			case KEY: {
				return STOP;
			}
			case BOMB: {
				return STOP;
			}
			case EXPLOSION: {
				return DESTROY;
				//or 
				return STOP;
			}
			default: {
				return -1; //means no collision
			}
			}
			break;
		}
		case WOLF: {
			switch (objectId2) {
			case DOOR: {
				//if collision statement
				//if no key 
				return STOP;
				// else if key and sheep
				//return pass
				//else return win code 4
			}
			case PLAYER: {
				//if collision statement
				return DESTROY;
			}
			case SHEEP: {
				return DESTROY;
			}
			case KEY: {
				return STOP;
			}
			case BOMB: {
				return STOP; //can return new result - run if needed for AI
			}
			case EXPLOSION: {
				return STOP;
			}
		
			}
			break;
		}

		case SHEEP: {
			switch (objectId2) {
				case SOFT_WALL: {
					return STOP;
				}
				case DISINTEGRATING_WALL: {
					return STOP;
				}
				case EMPTY_CELL: {
					return PASS;
				}
				case HARD_WALL: {
					return STOP;
				}
				case DOOR: {
					//if collision statement
					//if no key 
					return STOP;
					// else if key and sheep
					//return pass
					//else return win code 4
				}
				case PLAYER: {
					return STOP;
				}
				case SHEEP: {
					return STOP;
				}
				case KEY: {
					return PASS;
				}
				case BOMB: {
					return STOP; //can return new result - run if needed for AI
				}
				case EXPLOSION: {
					return STOP;
				}
				default: {
					return PASS;
				}

			}
			break;
		}
		case KEY: {
			switch (objectId2) {
			case SOFT_WALL: {
				return PASS;
			}
			case DISINTEGRATING_WALL: {
				return PASS;
			}
			case EMPTY_CELL: {
				return PASS;
			}
			case HARD_WALL: {
				return STOP;
			}
			case DOOR: {
				//if collision statement
				//if no key 
				return STOP;
				// else if key and sheep
				//return pass
				//else return win code 4
			}
			case PLAYER: {
				return STOP;
			}
			case SHEEP: {
				return STOP;
			}
			case BOMB: {
				return PASS;
			}
			case EXPLOSION: {
				return PASS;
			}
			default: {
				return PASS;
			}
			}
			break;
		}
		case BOMB: {
			switch (objectId2) {
			case SOFT_WALL: {
				return STOP;
			}
			case DISINTEGRATING_WALL: {
				return STOP;
			}
			case EMPTY_CELL: {
				return PASS;
			}
			case HARD_WALL: {
				return STOP;
			}
			case DOOR: {
				//if collision statement
				//if no key 
				return STOP;
				// else if key and sheep
				//return pass
				//else return win code 4
			}
			case PLAYER: {
				return PASS;
			}
			case SHEEP: {
				return PASS;
			}
			case BOMB: {
				return STOP;
			}
			case EXPLOSION: {
				return STOP;
			}
			case WOLF: {
				return STOP;
			}
			default: {
				return PASS;
			}
			}
			break;
		}
		case EXPLOSION: {
			switch (objectId2) {
			case SOFT_WALL: {
				return DESTROY;
			}
			case DISINTEGRATING_WALL: {
				return DESTROY;
			}
			case EMPTY_CELL: {
				return PASS;
			}
			case HARD_WALL: {
				return STOP;
			}
			case DOOR: {
				//if collision statement
				//if no key 
				return STOP;
				// else if key and sheep
				//return pass
				//else return win code 4
			}
			case PLAYER: {
				return PASS;
			}
			case SHEEP: {
				return PASS;
			}
			case BOMB: {
				return STOP;
			}
			case EXPLOSION: {
				return STOP;
			}
			case WOLF: {
				return STOP;
			}
			default: {
				return PASS;
			}
			}
			break;
		}
		default: {

			std::cout << "TEST 4" << std::endl;
			break;
		}
			
	}
	return 1;
	

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

