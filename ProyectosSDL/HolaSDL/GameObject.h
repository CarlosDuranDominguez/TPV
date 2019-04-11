#pragma once

#include <Box2D/Box2D.h>
#include <iterator>
#include <list>
#include "SDL.h"
#include "Texture.h"

enum GameObjects { kBlock, kWall, kBall, kPaddle, kButton, kAward, kCounter };
const string kGameObjectNames[]{"Block",  "Wall",  "Ball",   "Paddle",
                                "Button", "Award", "Counter"};
const int kGameObjectCount = 7;

/*
 *GameObject Abstract class
 */
class GameObject {
 protected:
  b2Vec2 position_;
  b2Vec2 size_;

 public:
  GameObject();
  GameObject(float32 x, float32 y, float32 width, float32 height);
  virtual ~GameObject();
  virtual void destroy();
  virtual void render() const;
  virtual void update();
  virtual void afterUpdate();
  virtual void handleEvents(SDL_Event event);
  virtual b2Vec2 getPosition() const;
  virtual void setPosition(float32 x, float32 y);
  virtual b2Vec2 getSize() const;
  virtual std::istream &deserialize(std::istream &out) = 0;
  virtual std::ostream &serialize(std::ostream &is) const = 0;
  friend std::istream &operator>>(std::istream &out, GameObject &object);
  friend std::ostream &operator<<(std::ostream &in, const GameObject &object);
};

std::istream &operator>>(std::istream &out, GameObject &object);
std::ostream &operator<<(std::ostream &in, const GameObject &object);
