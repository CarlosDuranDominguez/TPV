#include "EnlargenAward.h"
#include "Game.h"
#include "GameState.h"

EnlargenAward::EnlargenAward(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture)
	:Award(x, y, width, height, framerate, texture) {

}

void EnlargenAward::contact() {
	Award::contact();
	State::current->addEvent([]() {dynamic_cast<GameState*>(State::current)->paddle()->setWidth(200); });
}