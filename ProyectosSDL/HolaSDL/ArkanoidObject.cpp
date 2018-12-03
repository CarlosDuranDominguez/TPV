#pragma once

#include"ArkanoidObject.h"

void ArkanoidObject::render() const {
	SDL_Rect esto{ (int)getPosition().x, (int)getPosition().y, (int)getSize().x, (int)getSize().y };
	_texture->render(esto);
}