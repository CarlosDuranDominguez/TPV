#include "Game.h"

Game::Game() :
	window(nullptr), renderer(nullptr)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() < 0) {
		throw "Error loading the SDL font";
	}
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
	for (uint i = 0; i < NUMBER_TEXTURES; i++) {
		textures[i] = new Texture(renderer, TEXTURES[i].path, TEXTURES[i].rows, TEXTURES[i].columns);
	}
	fonts[0] = new Font(renderer, FONTSDIRECTORIES[REGULAR], 72);

	game = new GameState(this, renderer);
	menu = new MenuState(this, renderer);
	scoreboard = new ScoreBoardState(this, renderer);
	statemanager = new StateManager(game, menu, scoreboard);
	gamemanager = new GameManager();
}

Game::~Game() 
{
	delete game;
	delete menu;
	delete scoreboard;
	for (uint i = 0; i < NUMBER_TEXTURES; i++) {
		delete textures[i];
	}
	delete fonts[0];
	delete gamemanager;
	delete statemanager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

Texture** Game::getTextures() {
	return textures;
}

Font** Game::getFonts() {
	return fonts;
}

void Game::run() {
	statemanager->run();
}

void Game::changeState(string stateName) {
	statemanager->changeState(stateName);
}

