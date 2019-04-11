#pragma once

#include <Box2D/Box2D.h>
#include <functional>
#include <list>
#include <stack>
#include "ArkanoidTimer.h"
#include "GameObject.h"
#include "SDL.h"

class Game;
class CollisionLogic;

class State {
  class NewInstance {
   public:
    NewInstance(GameObjects type, b2Vec2 &position);
    ;
    GameObjects type_;
    b2Vec2 position_;
  };

 protected:
  SDL_Renderer *renderer_ = nullptr;
  list<GameObject *> gameObjects_;
  list<GameObject *> pendingOnDestroy_;
  list<NewInstance *> pendingOnCreate_;
  stack<function<void()>> pendingEvents_;
  CollisionLogic *listenerLogic_;
  b2World *world_;
  ArkanoidTimer *stateTime_;
  bool exit_ = false;
  Game *game_;
  virtual void _end();

 public:
  State();
  State(Game *game, SDL_Renderer *renderer);
  virtual ~State();
  static State *current_;
  virtual void end();
  virtual void reset();
  virtual void init();

  void create();
  void render() const;
  void update();
  void handleEvents();
  void fixUpdate(float32 time) const;
  void afterUpdate();
  void events();
  virtual void destroy();

  bool finished() const;

  void destroy(GameObject *gameObject);
  void addCreation(GameObjects type, b2Vec2 &position);
  GameObject *create(GameObjects type, b2Vec2 &position);
  void add(GameObject &gameObject);
  void addEvent(const function<void()> &);
  float32 getTime() const;
};
