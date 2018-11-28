#pragma once

#include <list>
#include "SDL.h"
#include<Box2D/Box2D.h>
#include "GameObject.h"
#include "Renderable.h"
#include "Controllable.h"
#include "Updatable.h"

class Game;

class State
{
  protected:
	SDL_Renderer *_renderer = nullptr;
	list<GameObject*> _gameObjects;
	list<Renderable*> _renderableGameObjects;
	list<Controllable*> _controllableGameObjects;
	list<Updatable*> _updatableGameObjects;
	b2World *_world;
	bool _exit = false;
	Game *_game;
	void _render() const;
	void _update();
	void _handleEvents();
	void _fixUpdate(float32 time);
	virtual void _end() {};
  public:
	State() {};
	State(Game *game, SDL_Renderer *renderer);
	~State();
	virtual void init() {};
	void run();
	virtual void load(string& filename);
	virtual void save(string& filename);
};
