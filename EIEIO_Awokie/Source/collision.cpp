#include "collision.h"
#include <iostream>
//collilde()
int collide(int objectId, int objectId2, int xPos, int yPos, int xPos2, int yPos2) {
	switch (objectId) {
		case 1: {
			//return 
			std::cout << "TEST 1" << std::endl;
			break;
		}
		case 2: {
			std::cout << "TEST 2" << std::endl;
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

