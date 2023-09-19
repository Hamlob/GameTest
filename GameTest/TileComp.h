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


	TileComp() = default;
	TileComp(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
	}

	//creates transform and sprite components with corresponding dimensions (transform) and texture(sprite) to it
	void init() override {
		entity->addComponent<TransformComp>(tileRect.x, tileRect.y, tileRect.h, tileRect.w);
		transform = &entity->getComponent<TransformComp>();

		entity->addComponent<SpriteComp>(tileID);
		sprite = &entity->getComponent<SpriteComp>();

	}
};

