#include "GameState.h"
#include "Game.h"
#include "LoadManager.h"

/**
 * Constructor.
 */
GameState::GameState(Game *game, SDL_Renderer *renderer)
	: _renderer(renderer), _game(game), _exit(false), _gameover(false), _win(false)
{
	_timer = new Timer(0, 0, 300, 50, WHITE, _game->getFonts()[MEDIUMFONT]);
	Texture **textures = _game->getTextures();
	int wall_width = textures[TOPSIDE]->getH() * WIN_WIDTH / textures[TOPSIDE]->getW();
	int wall_height = WIN_HEIGHT - textures[TOPSIDE]->getH() * WIN_WIDTH / textures[TOPSIDE]->getW();
	_ball = new Ball(
		(WIN_WIDTH - textures[BALL]->getW() / 4) / 2,
		WIN_HEIGHT * 14 / 16,
		textures[BALL]->getW() / 4,
		textures[BALL]->getH() / 4,
		textures[BALL],
		this);
	_paddle = new Paddle(
		_game,
		(WIN_WIDTH - textures[PADDLE]->getW()) / 2,
		WIN_HEIGHT * 15 / 16,
		textures[PADDLE]->getW(),
		textures[PADDLE]->getH(),
		PADDLESPEED,
		textures[PADDLE]);
	_upWall = new Wall(
		0,
		50,
		WIN_WIDTH,
		wall_width,
		textures[TOPSIDE]);
	_leftWall = new Wall(
		0,
		wall_width+50,
		wall_width,
		wall_height,
		textures[SIDE]);
	_rightWall = new Wall(
		WIN_WIDTH - wall_width,
		wall_width+50,
		wall_width,
		wall_height,
		textures[SIDE]);
	_blocksmap = new BlocksMap(wall_width, 50, WIN_WIDTH - 2*wall_width,WIN_HEIGHT/2 - wall_width);
}

/**
 * Destructor.
 */
GameState::~GameState()
{
	delete _ball;
	delete _paddle;
	delete _blocksmap;
	delete _upWall;
	delete _rightWall;
	delete _leftWall;
	delete _timer;
}

/**
 * Initialize the varibles of the game.
 */
void GameState::init()
{
	_exit = false;
	_gameover = false;
	_win = false;
	_ball->setPosition((WIN_WIDTH - _game->getTextures()[BALL]->getW() / 4) / 2, WIN_HEIGHT * 14 / 16);
	_ball->setVelocity(0, 150);
	_paddle->setPosition((WIN_WIDTH - _game->getTextures()[PADDLE]->getW()) / 2, WIN_HEIGHT * 15 / 16);
	_blocksmap->loadMap( LEVEL[_game->gameManager()->level()], _game->getTextures()[BRICKS]);
	_timer->reset();
}

/**
 * Execute the loop of the state.
 */
void GameState::run()
{
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!_exit && !_gameover && !_win)
	{
		_handleevents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAMERATE)
		{
			_update();
			startTime = SDL_GetTicks();
		}
		_render();
		_win = _blocksmap->numberOfBlocks() == 0;
		_gameover = _ball->position().getY() > WIN_HEIGHT;
	}
	if (_exit)
	{
		_game->changeState("gameover");
	}
	else if (_gameover)
	{
		_game->gameManager()->reset();
		_game->changeState("scoreboard");
	}
	else
	{
		_game->gameManager()->finishLevel(_timer->getTime());
		if (_game->gameManager()->level() == 2) {
			_game->gameManager()->reset();
			_game->changeState("scoreboard");
		}
		else
		{
			_game->changeState("game");
		}
	}
	LoadManager::save(_game, "../saves/level.save");
}

/**
 * It updates the position of the objects.
 */
void GameState::_update()
{
	_ball->update();
	_paddle->update();
	_timer->update();
}

/**
 * It renders the objects.
 */
void GameState::_render() const
{
	SDL_RenderClear(_renderer);
	_blocksmap->render();
	_ball->render();
	_paddle->render();
	_upWall->render();
	_rightWall->render();
	_leftWall->render();
	_timer->render();
	SDL_RenderPresent(_renderer);
}

/**
 * It detects user input.
 */
void GameState::_handleevents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !_exit)
	{
		if (event.type == SDL_QUIT)
			_exit = true;
		_paddle->handleEvents(event);
	}
}

/**
 * It detects if the circular object collides with any object and return the normal vector and the position of the collision.
 */
bool GameState::collides(const Ball *object, Vector2D &collisionPosition, Vector2D &reflection) const
{
	return _blocksmap->collide(object, collisionPosition, reflection) ||
		   _paddle->collide(object, collisionPosition, reflection) ||
		   _leftWall->collide(object, collisionPosition, reflection) ||
		   _upWall->collide(object, collisionPosition, reflection) ||
		   _rightWall->collide(object, collisionPosition, reflection);
}
