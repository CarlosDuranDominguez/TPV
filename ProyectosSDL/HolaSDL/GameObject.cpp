#include "GameObject.h"
#include "State.h"

GameObject::GameObject() = default;

GameObject::GameObject(const float32 x, const float32 y, const float32 width,
                       const float32 height)
    : position_(x, y), size_(width, height) {}

// Destroys this game object from the current state in the game
GameObject::~GameObject() = default;

void GameObject::render() const {}

void GameObject::update() {}

void GameObject::afterUpdate() {}

void GameObject::handleEvents(SDL_Event) {}

void GameObject::destroy() { State::current_->destroy(this); }

// Sets this game object's position
void GameObject::setPosition(const float32 x, const float32 y) {
  position_.Set(x, y);
}

// Gets this game object's position
b2Vec2 GameObject::getPosition() const { return position_; }

// Gets this game object's size
b2Vec2 GameObject::getSize() const { return size_; }

// Sets the operator overload for input streams
std::istream &operator>>(std::istream &out, GameObject &object) {
  // Deserialize the object
  return object.deserialize(out);
}

// Sets the operator overload for output streams
std::ostream &operator<<(std::ostream &in, const GameObject &object) {
  // Serialize the object
  return object.serialize(in);
}
