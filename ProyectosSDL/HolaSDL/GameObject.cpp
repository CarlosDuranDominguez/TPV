#include "GameObject.h"
#include "State.h"

GameObject::GameObject() {}  /// Public Virtual
GameObject::GameObject(float32 x, float32 y, float32 width, float32 height)
    : position_(x, y),
      size_(width, height) {
}  // Destroys this game object from the current state in the game
GameObject::~GameObject() {}

list<GameObject *>::iterator GameObject::getId() const { return id_; }

list<GameObject *>::iterator GameObject::setId(
    list<GameObject *>::iterator &id) {
  return id_ = id;
}

void GameObject::render() const {}

void GameObject::update() {}

void GameObject::afterUpdate() {}

void GameObject::handleEvents(SDL_Event event) {}

void GameObject::destroy() { State::current_->destroy(id_); }

/// Public Virtual
// Sets this game object's position
void GameObject::setPosition(float32 x, float32 y) { position_.Set(x, y); }

/// Public Virtual
// Gets this game object's position
b2Vec2 GameObject::getPosition() const { return position_; }

/// Public Virtual
// Gets this game object's size
b2Vec2 GameObject::getSize() const { return size_; }

/// Friend
// Sets the operator overload for input streams
std::istream &operator>>(std::istream &out, GameObject &object) {
  // Deserialize the object
  return object.deserialize(out);
}

/// Friend
// Sets the operator overload for output streams
std::ostream &operator<<(std::ostream &in, const GameObject &object) {
  // Serialize the object
  return object.serialize(in);
}
