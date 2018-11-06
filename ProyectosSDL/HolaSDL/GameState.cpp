#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* game, SDL_Renderer* renderer) : 
	renderer(renderer), game(game), exit(false), gameover(false), win(false) {
	timer = new Timer(0, 0, 300, 50, WHITE, game->getFonts()[0]);
	Texture** textures = game->getTextures();
	int wall_width = textures[TOPSIDE]->getH()*WIN_WIDTH / textures[TOPSIDE]->getW();
	int wall_height = WIN_HEIGHT - textures[TOPSIDE]->getH()*WIN_WIDTH / textures[TOPSIDE]->getW();
	ball = new Ball((WIN_WIDTH - textures[BALL]->getW() / 4) / 2,
		WIN_HEIGHT * 14 / 16,
		textures[BALL]->getW() / 4,
		textures[BALL]->getH() / 4,
		textures[BALL],
		this);
	paddle = new Paddle((WIN_WIDTH - textures[PADDLE]->getW()) / 2,
		WIN_HEIGHT * 15 / 16,
		textures[PADDLE]->getW(),
		textures[PADDLE]->getH(),
		PADDLESPEED,
		textures[PADDLE]);
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
	blocksmap = nullptr;
}

GameState::~GameState() {
	delete ball;
	delete paddle;
	delete blocksmap;
	delete upWall;
	delete rightWall;
	delete leftWall;
	delete timer;
}

void GameState::init() {
	exit = false; gameover = false; win = false;
	ball->setPosition((WIN_WIDTH - game->getTextures()[BALL]->getW() / 4) / 2, WIN_HEIGHT * 14 / 16);
	ball->setVelocity(0, 150);
	paddle->setPosition((WIN_WIDTH - game->getTextures()[PADDLE]->getW()) / 2, WIN_HEIGHT * 15 / 16);
	if( blocksmap != nullptr ) delete blocksmap;
	blocksmap = new BlocksMap(LEVEL[0], game->getTextures()[TOPSIDE]->getH()*WIN_WIDTH / game->getTextures()[TOPSIDE]->getW(), game->getTextures()[BRICKS]);
	timer->reset();
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
		win = blocksmap->numberOfBlocks() == 0;
		gameover = ball->position().getY() > WIN_HEIGHT;
	}
	if (exit) game->changeState("gameover");
	else if (gameover) game->changeState("scoreboard");
}

void GameState::update()
{
	ball->update();
	paddle->update();
	timer->update();
}

void GameState::render() const
{
	SDL_RenderClear(renderer);
	blocksmap->render();
	ball->render();
	paddle->render();
	upWall->render();
	rightWall->render();
	leftWall->render();
	timer->render();
	SDL_RenderPresent(renderer);
}

void GameState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		paddle->handleEvents(event);
	}
}

bool GameState::collides(const Ball* object, Vector2D& collisionPosition, Vector2D& reflection) {
	return blocksmap->collide(object, collisionPosition, reflection) ||
		paddle->collide(object, collisionPosition, reflection) ||
		leftWall->collide(object, collisionPosition, reflection) ||
		upWall->collide(object, collisionPosition, reflection) ||
		rightWall->collide(object, collisionPosition, reflection);
}