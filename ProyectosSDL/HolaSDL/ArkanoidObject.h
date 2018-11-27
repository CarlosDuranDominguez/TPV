#pragma once

#include "GameObject.h"
#include "Texture.h"

class ArkanoidObject : public GameObject, public Renderable, public Updatable {
public:
	ArkanoidObject(double x, double y, double width, double height, Texture* texture) 
		: GameObject(x, y, width, height), Renderable(texture), Updatable() {};
	~ArkanoidObject() {};
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual std::ostream& toOutStream(std::ostream& out) = 0;
	virtual std::istream& fromInStream(std::istream& is) = 0;
};
