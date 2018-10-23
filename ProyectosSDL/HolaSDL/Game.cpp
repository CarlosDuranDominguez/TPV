#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"

Game::Game() :
	window(nullptr), renderer(nullptr),	exit(false), gameover(false), win(false) 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
	for (uint i = 0; i < NUMBER_TEXTURES; i++) {
		textures[i] = new Texture(renderer, TEXTURES[i].path, TEXTURES[i].rows, TEXTURES[i].columns);
	}

	int wall_width = textures[TOPSIDE]->getH()*WIN_WIDTH / textures[TOPSIDE]->getW();
	int wall_height = WIN_HEIGHT - textures[TOPSIDE]->getH()*WIN_WIDTH / textures[TOPSIDE]->getW();
	ball = new Ball((WIN_WIDTH- textures[BALL]->getW()/4)/2, 
		WIN_HEIGHT*14/16, 
		textures[BALL]->getW()/4, 
		textures[BALL]->getH()/4, 
		textures[BALL], 
		this);
	paddle = new Paddle((WIN_WIDTH- textures[PADDLE]->getW()) /2,
		WIN_HEIGHT*15/16, 
		textures[PADDLE]->getW(), 
		textures[PADDLE]->getH(), 
		PADDLESPEED, 
		textures[PADDLE]);
	blocksmap = new BlocksMap(LEVEL[0], wall_width,textures[BRICKS]);
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

};
Game::~Game() 
{
	delete ball;
	delete paddle;
	delete blocksmap;
	delete upWall;
	delete rightWall;
	delete leftWall;
	for (uint i = 0; i < NUMBER_TEXTURES; i++) {
		delete textures[i];
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};
void Game::run()
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
		//collides();
		render();
	}
};

void Game::update()
{
	ball->update();
	paddle->update();
};
void Game::render() const 
{
	SDL_RenderClear(renderer);
	blocksmap->render();
	ball->render();
	paddle->render();
	upWall->render();
	rightWall->render();
	leftWall->render();
	SDL_RenderPresent(renderer);
};
void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) 
			exit = true;
		paddle->handleEvents(event);
	}
};
void Game::collides() {

};

