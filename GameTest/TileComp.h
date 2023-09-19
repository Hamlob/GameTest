#pragma once
#include "ECS.h"
#include "TransformComp.h"
#include "SpriteComp.h"

class TileComp: public Component
{
public:
	TransformComp* transform;
	SpriteComp* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;


	TileComp() = default;
	TileComp(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "textures/water.png";
			break;
		case 1:
			path = "textures/grass.png";
			break;
		case 2:
			path = "textures/earth.png";
		default:
			break;
		}
	}

	//creates transform and sprite components with corresponding dimensions (transform) and texture(sprite) to it
	void init() override {
		entity->addComponent<TransformComp>(tileRect.x, tileRect.y, tileRect.h, tileRect.w);
		transform = &entity->getComponent<TransformComp>();

		entity->addComponent<SpriteComp>(path);
		sprite = &entity->getComponent<SpriteComp>();

	}
};

