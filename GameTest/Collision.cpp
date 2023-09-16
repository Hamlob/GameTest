#include "Collision.h"


bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB){

	if (
		rectA.x + rectA.w >= rectB.x &&			//overlap of A and B in the x axis
		rectB.x + rectB.w >= rectA.x &&			//overlap of A and B in the x axis
		rectA.y + rectA.h >= rectB.y &&			//overlap of A and B in the y axis
		rectB.y + rectB.h >= rectA.y			//overlap of A and B in the y axis
		)
	{
		return true;
	}
	return false;
}
