#include "Game.h"

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
	ball = new Ball(0, 0, textures[BALL]->getW(), textures[BALL]->getH(), textures[BALL], this);
	//paddle = new Paddle(0, 0, textures[PADDLE]->getW(), textures[PADDLE]->getH(), textures[PADDLE]);
	//blocksmap = new BlocksMap(LEVEL[0]);
	//upWall = new Wall(0,0,textures[TOPSIDE]->getW(),textures[TOPSIDE]->getH(),textures[TOPSIDE]);
	//rightWall = new Wall(0, 0, textures[SIDE]->getW(), textures[SIDE]->getH(), textures[SIDE]); 
	//leftWall = new Wall(0, 0, textures[SIDE]->getW(), textures[SIDE]->getH(), textures[SIDE]);

};
Game::~Game() 
{
	delete ball;
	//delete paddle;
	//delete blocksmap;
	for (uint i = 0; i < NUMBER_TEXTURES; i++) {
		delete textures[i];
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};
void Game::run()
{
	int startTime, frameTime;
	while (!exit && !gameover && !win) {
		//handleEvents();
		//update();
		//collides();
		render();
	}
};

void Game::update()
{
	ball->update();
	//paddle->update();
};
void Game::render() const 
{
	SDL_RenderClear(renderer);
	ball->render();

	//paddle->render();
	//blocksmap->render();
	//upWall->render();
	//rightWall->render();
	//leftWall->render();
	SDL_RenderPresent(renderer);
};
void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) 
			exit = true;
		//paddle->handleEvents(event);
	}
};
void Game::collides() {

};

