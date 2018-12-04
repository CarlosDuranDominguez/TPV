#include "NextLevelAward.h"
#include "Game.h"
#include "GameState.h"

NextLevelAward::NextLevelAward(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture)
	:Award(x, y, width, height, framerate, texture) {

}

void NextLevelAward::contact() {
	Award::contact();
	State::current->addEvent([]() {Game::gameManager()->finishLevel(State::current->getTime()); });
}