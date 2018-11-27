#pragma once

#include "SDL.h"
#include <Box2D/Box2D.h>
#include "Texture.h"

/*
 *Renderable interface
 */
class Renderable {
protected: 
	Texture* _texture;
public: 
	Renderable(Texture* texture) :_texture(texture) {};
	~Renderable() {};
	virtual void render() const = 0;
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
class GameObject {
protected:
	b2Vec2 _position;
	b2Vec2 _size;
public:
	GameObject(double x, double y, double width, double height) : _position(x, y), _size(width, height) {};
	~GameObject() {};
	virtual std::ostream& toOutStream(std::ostream& out) const = 0;
	virtual std::istream& fromInStream(std::istream& is) const = 0;
	friend std::ostream& operator>>(std::ostream& out, const GameObject& object);
	friend std::istream& operator<<(std::istream& out, const GameObject& object);
};

std::ostream& operator>>(std::ostream& out, const GameObject& object) {
	return object.toOutStream(out);
}

std::istream& operator<<(std::istream& in, const GameObject& object) {
	return object.fromInStream(in);
}