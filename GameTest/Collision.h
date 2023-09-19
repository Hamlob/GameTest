#pragma once
#include <SDL.h>

class ColliderComp;	//forward declaration to let this file know the ColliderComp exists somewhere

class Collision
{
public:
	//overloaded function to take either 2 rectangles or 2 collaiders
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);	//axis align bounding box
	static bool AABB(const ColliderComp& colA, const ColliderComp& colB); 
};

