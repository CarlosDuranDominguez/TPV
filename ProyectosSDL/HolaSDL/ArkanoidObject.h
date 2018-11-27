#pragma once

#include "GameObject.h"
#include "Texture.h"

class ArkanoidObject : public GameObject {
protected:
	int _width, _heigth;
	Texture* _texture;
public:
	ArkanoidObject(double x, double y, int width, int height, Texture* texture) 
		: GameObject(x, y), _width(width), _heigth(height), _texture(texture) {};
	~ArkanoidObject() {};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual std::ostream& toStream(std::ostream& out) = 0;
	virtual std::istream& intoStream(std::istream& is) = 0;
};