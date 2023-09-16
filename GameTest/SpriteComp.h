#pragma once
#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"

class SpriteComp : public Component {
private:
	TransformComp* _transform_p;
	SDL_Texture* _texture_p;
	SDL_Rect _srcRect, _destRect;

public:

	SpriteComp() = default;
	SpriteComp(const char* path) {
		setTexture(path);
	}

	~SpriteComp() {
		SDL_DestroyTexture(_texture_p);
	}

	void setTexture(const char* path) {
		_texture_p = TextureManager::LoadTexture(path);
	}

	void init() override {
		_transform_p = &entity_p->getComponent<TransformComp>();

		_srcRect.x = _srcRect.y = 0;
		_srcRect.w = _transform_p->width;
		_srcRect.h = _transform_p->height;

	}

	void update() override {
		_destRect.x = static_cast<int>(_transform_p->position.x);
		_destRect.y = static_cast<int>(_transform_p->position.y);
		_destRect.w = _transform_p->width * _transform_p->scale;
		_destRect.h = _transform_p->height * _transform_p->scale;
	}

	void draw() override {
		TextureManager::Draw(_texture_p, _srcRect, _destRect);
	}
};
