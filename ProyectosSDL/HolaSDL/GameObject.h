#pragma once

#include "SDL.h"
#include <Box2D/Box2D.h>
#include "Texture.h"


const enum GAME_OBJECTS{block, wall, ball, paddle, button, award, counter};
const string GAME_OBJECT_NAMES []{"Block", "Wall", "Ball", "Paddle", "Button", "Award", "Counter"};
const int GAME_OBJECT_COUNT = 7;

/*
 *GameObject Abstract class
 */
class GameObject {
protected:
	b2Vec2 _position;
	b2Vec2 _size;
public:
	GameObject() {};
	GameObject(float32 x, float32 y, float32 width, float32 height) : _position(x, y), _size(width, height) {};
	~GameObject() {};
	virtual std::istream& deserialize(std::istream& out) = 0;
	virtual std::ostream& serialize(std::ostream& is) const = 0;
	friend std::istream& operator>>(std::istream& out, GameObject& object);
	friend std::ostream& operator<<(std::ostream& out, const GameObject& object);
};

std::istream& operator>>(std::istream& out, GameObject& object);

std::ostream& operator<<(std::ostream& in, const GameObject& object);

std::istream& operator>>(std::istream& out, GAME_OBJECTS& object);
