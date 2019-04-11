#include "GameObject.h"
#include "State.h"

/// Public Virtual
// Destroys this game object from the current state in the game
void GameObject::destroy() { State::current->destroy(_id); }

/// Public Virtual
// Sets this game object's position
void GameObject::setPosition(float32 x, float32 y) { _position.Set(x, y); }

/// Public Virtual
// Gets this game object's position
b2Vec2 GameObject::getPosition() const { return _position; }

/// Public Virtual
// Gets this game object's size
b2Vec2 GameObject::getSize() const { return _size; }

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
