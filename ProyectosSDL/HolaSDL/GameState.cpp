#include "GameState.h"
#include "Block.h"
#include "Game.h"

void GameState::init()
{
	GameObject *gameObject = new Block(5,5,10,10,1,_game->getTextures()[BRICKS],*_world);
	//static_cast<Block*>(gameObject)->Init(*_world, _game->getTextures()[BRICKS]);
	_gameObjects.push_back(gameObject);
	_renderableGameObjects.push_back(dynamic_cast<Renderable*>(gameObject));
}
void GameState::_end(){}