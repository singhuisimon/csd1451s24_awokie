#include "collision.h"
#include "enum.h"
#include <iostream>
//collilde()
int collide(int objectId, int objectId2, int xPos, int yPos, int xPos2, int yPos2) {
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

