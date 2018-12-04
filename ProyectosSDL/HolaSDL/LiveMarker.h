#pragma once

#include "GameObject.h"
#include "Renderable.h"

class LiveMarker : public GameObject, public Renderable
{
  public:
	LiveMarker(float32 x, float32 y, float32 width, float32 height, Texture *texture);
	void render() const;
	virtual std::istream &deserialize(std::istream &out);
	virtual std::ostream &serialize(std::ostream &is) const;
};
