#include "StickyAward.h"
#include "Game.h"
#include "State.h"

StickyAward::StickyAward(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture)
	:Award(x, y, width, height, framerate, texture) {

}

void StickyAward::contact() {

}