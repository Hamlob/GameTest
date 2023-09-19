#pragma once
#include "ECS.h"
#include "Vector2D.h"

/**
	 * .
	 *
	 * \param (none)
	 * \param (x, y)
	 * \param (x, y, h, w, scale=1)
	 */
class TransformComp : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	//object dimensions
	int height = 32;
	int width = 32;
	int scale = 1;

	//object movement speed
	int speed = 3;

	TransformComp() {
		position.setZero();
	}

	TransformComp(float x, float y) {
		position.x = x;
		position.y = y;
	}
	
	TransformComp(float x, float y, int h, int w, int sc = 1) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.setZero();
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};

