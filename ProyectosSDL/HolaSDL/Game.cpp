#include "Game.h"

Game::Game()
	: _window(nullptr), _renderer(nullptr)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() < 0)
	{
		throw "Error loading the SDL font";
	}
	_window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_window == nullptr || _renderer == nullptr)
		throw "Error loading the SDL window or renderer";
	for (uint i = 0; i < NUMBER_TEXTURES; i++)
	{
		_textures[i] = new Texture(_renderer, TEXTURES[i].path, TEXTURES[i].rows, TEXTURES[i].columns);
	}
	_fonts[0] = new Font(_renderer, FONTSDIRECTORIES[REGULAR], 72);

	_game = new GameState(this, _renderer);
	_menu = new MenuState(this, _renderer);
	_scoreboard = new ScoreBoardState(this, _renderer);
	_statemanager = new StateManager(_game, _menu, _scoreboard);
	_gamemanager = new GameManager();
}

Game::~Game()
{
	delete _game;
	delete _menu;
	delete _scoreboard;
	for (uint i = 0; i < NUMBER_TEXTURES; i++)
	{
		delete _textures[i];
	}
	delete _fonts[0];
	delete _gamemanager;
	delete _statemanager;
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	SDL_Quit();
}

Texture **Game::getTextures()
{
	return _textures;
}

Font **Game::getFonts()
{
	return _fonts;
}

void Game::run()
{
	_statemanager->run();
}

void Game::changeState(string stateName)
{
	_statemanager->changeState(stateName);
}
