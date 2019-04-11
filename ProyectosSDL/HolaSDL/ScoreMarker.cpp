#include "ScoreMarker.h"
#include "Game.h"

/// Public
// Constructor
ScoreMarker::ScoreMarker(float32 x, float32 y, float32 width, float32 height,
                         SDL_Color color, Font *font)
    : Text(font, x, y, width, height, color, "h") {
  _score = Game::getGameManager()->getScore();
  setText(to_string(_score));
}

/// Public Virtual
// Updates the update behaviour
void ScoreMarker::update() {
  if (_score != Game::getGameManager()->getScore()) {
    _score = Game::getGameManager()->getScore();
    setText(to_string(_score));
  }
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &ScoreMarker::deserialize(std::istream &out) { return out; }

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &ScoreMarker::serialize(std::ostream &is) const { return is; }
