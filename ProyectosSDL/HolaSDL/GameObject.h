#pragma once

#include "SDL.h"
#include<Box2D/Box2D.h>
#include"te"

/*
 *Renderable interface
 */
class Renderable {
protected: 

public: 
	~Renderable() {};
	virtual void render() = 0;
};

/*
 *Updatable interface
 */
class Updatable {
public:
	~Updatable() {};
	virtual void update() = 0;
};

/*
 *Controllable interface
 */
class Controllable {
public:
	~Controllable() {};
	virtual void handleEvents(SDL_Event event) = 0;
};

/*
 *GameObject Abstract class
 */
class GameObject: public Renderable, public Updatable {
protected:
	b2Vec2 _position;
public:
	GameObject(double x, double y) : _position(x, y) {};
	~GameObject() {};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual std::ostream& toStream(std::ostream& out) = 0;
	virtual std::istream& intoStream(std::istream& is) = 0;
};