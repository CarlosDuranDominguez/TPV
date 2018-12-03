#pragma once

#include "SDL.h"
#include <Box2D/Box2D.h>
#include "Texture.h"
#include <list>
#include <iterator>


const enum GAME_OBJECTS{block, wall, ball, paddle, button, award, counter};
const string GAME_OBJECT_NAMES []{"Block", "Wall", "Ball", "Paddle", "Button", "Award", "Counter"};
const int GAME_OBJECT_COUNT = 7;

/*
 *GameObject Abstract class
 */
class GameObject {
protected:
	list<GameObject*>::iterator _id;
	b2Vec2 _position;
	b2Vec2 _size;
public:
	GameObject() {};
	GameObject(float32 x, float32 y, float32 width, float32 height) : _position(x, y), _size(width, height) {};
	virtual ~GameObject() {};
	list<GameObject*>::iterator getId() const { return _id; };
	list<GameObject*>::iterator setId(list<GameObject*>::iterator& id) { return _id = id; };
	virtual void destroy();
	virtual void render() const {};
	virtual void update() {};
	virtual void handleEvents(SDL_Event event) {};
	virtual b2Vec2 getPosition() const;
	virtual b2Vec2 getSize() const;
	virtual std::istream& deserialize(std::istream& out) = 0;
	virtual std::ostream& serialize(std::ostream& is) const = 0;
	friend std::istream& operator>>(std::istream& out, GameObject& object);
	friend std::ostream& operator<<(std::ostream& out, const GameObject& object);
};

std::istream& operator>>(std::istream& out, GameObject& object);

std::ostream& operator<<(std::ostream& in, const GameObject& object);

std::istream& operator>>(std::istream& out, GAME_OBJECTS& object);
