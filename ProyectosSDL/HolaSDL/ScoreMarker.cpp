#include "ScoreMarker.h"
#include "Game.h"

// Constructor
ScoreMarker::ScoreMarker(const float32 x, const float32 y, const float32 width,
                         const float32 height, const SDL_Color color,
                         Font *font)
    : Text(font, x, y, width, height, color, "h") {
  score_ = Game::getGameManager()->getScore();
  setText(to_string(score_));
}

ScoreMarker::~ScoreMarker() = default;

// Updates the update behaviour
void ScoreMarker::update() {
  if (score_ != Game::getGameManager()->getScore()) {
    score_ = Game::getGameManager()->getScore();
    setText(to_string(score_));
  }
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &ScoreMarker::deserialize(std::istream &out) { return out; }

// Defines the serialize method behaviour to save the data into a file save
std::ostream &ScoreMarker::serialize(std::ostream &is) const { return is; }
