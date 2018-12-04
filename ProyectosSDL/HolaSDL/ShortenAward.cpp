#include "ShortenAward.h"
#include "Game.h"
#include "GameState.h"

ShortenAward::ShortenAward() {};
ShortenAward::ShortenAward(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture)
	:Award(x, y, width, height, framerate, texture) {}

void ShortenAward::contact() {
	Award::contact();
	State::current->addEvent([]() {dynamic_cast<GameState*>(State::current)->paddle()->setWidth(50); });
}