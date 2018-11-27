#pragma once

#include"ArkanoidObject.h"

void ArkanoidObject::render() const {
	_texture->render(SDL_Rect{ _position.x,_position.y,_size.x,_size.y });
}