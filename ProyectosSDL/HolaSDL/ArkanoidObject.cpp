#pragma once

#include"ArkanoidObject.h"

void ArkanoidObject::render() const {
	_texture->render(SDL_Rect{ (int)_position.x, (int)_position.y, (int)_size.x, (int)_size.y });
}