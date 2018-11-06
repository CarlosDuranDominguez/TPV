#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* game) : 
	renderer(renderer), exit(false), gameover(false), win(false) {

	texts[0] = new Text(game->getFonts()[0], 0, 0, 200, 50, { 255,255,255,255 }, "Hola");

	int wall_width = textures[TOPSIDE]->getH()*WIN_WIDTH / textures[TOPSIDE]->getW();
	int wall_height = WIN_HEIGHT - textures[TOPSIDE]->getH()*WIN_WIDTH / textures[TOPSIDE]->getW();
	ball = new Ball((WIN_WIDTH - textures[BALL]->getW() / 4) / 2,
		WIN_HEIGHT * 14 / 16,
		textures[BALL]->getW() / 4,
		textures[BALL]->getH() / 4,
		textures[BALL],
		this);
	ball->setVelocity(0, 150);
	paddle = new Paddle((WIN_WIDTH - textures[PADDLE]->getW()) / 2,
		WIN_HEIGHT * 15 / 16,
		textures[PADDLE]->getW(),
		textures[PADDLE]->getH(),
		PADDLESPEED,
		textures[PADDLE]);
	blocksmap = new BlocksMap(LEVEL[0], wall_width, textures[BRICKS]);
	upWall = new Wall(0,
		0,
		WIN_WIDTH,
		wall_width,
		textures[TOPSIDE]);
	leftWall = new Wall(0,
		wall_width,
		wall_width,
		wall_height,
		textures[SIDE]);
	rightWall = new Wall(WIN_WIDTH - wall_width,
		wall_width,
		wall_width,
		wall_height,
		textures[SIDE]);
}

GameState::~GameState() {
	delete ball;
	delete paddle;
	delete blocksmap;
	delete upWall;
	delete rightWall;
	delete leftWall;
	delete texts[0];
	delete[] texts;
}

void GameState::run()
{
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit && !gameover && !win) {
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAMERATE) {
			update();
			startTime = SDL_GetTicks();
		}
		render();
	}
};

void GameState::update()
{
	ball->update();
	paddle->update();
};
void GameState::render() const
{
	SDL_RenderClear(renderer);
	blocksmap->render();
	ball->render();
	paddle->render();
	upWall->render();
	rightWall->render();
	leftWall->render();
	texts[0]->render();
	SDL_RenderPresent(renderer);
};
void GameState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		paddle->handleEvents(event);
	}
};
bool GameState::collides(const Ball* object, Vector2D& collisionPosition, Vector2D& reflection) {
	return blocksmap->collide(object, collisionPosition, reflection) ||
		paddle->collide(object, collisionPosition, reflection) ||
		leftWall->collide(object, collisionPosition, reflection) ||
		upWall->collide(object, collisionPosition, reflection) ||
		rightWall->collide(object, collisionPosition, reflection);
};
