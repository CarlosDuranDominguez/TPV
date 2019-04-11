#include "ScoreBoard.h"
#include <fstream>
#include <iostream>
#include "Game.h"

// Constructor
ScoreBoard::ScoreBoard(Font *font, const float32 x, const float32 y,
                       const float32 width, const float32 height,
                       const SDL_Color color)
    : GameObject(x, y, width, height), font_(font), color_(color) {
  auto scores = Game::getGameManager()->getScores();
  auto j = 0;
  for (auto score : scores) {
    if (j == 10) break;
    texts_[j] =
        new Text(font_, position_.x, position_.y + getSize().y * j, getSize().x,
                 getSize().y, color_,
                 to_string(j + 1) + "\u00ba " + score->name + " " +
                     to_string(score->score) + " " + to_string(score->time));
    j++;
  }
  for (auto i = scores.size(); i < 10; i++) {
    auto aux = to_string(i + 1) + "\u00ba ------ ------ ------";
    texts_[i] = new Text(font_, position_.x, position_.y + getSize().y * i,
                         getSize().x, getSize().y, color_, aux);
  }
}

// Destructor
ScoreBoard::~ScoreBoard() {
  for (auto text : texts_) {
    delete text;
  }
}

// Creates the first ten games.
void ScoreBoard::rewrite() {
  auto scores = Game::getGameManager()->getScores();
  auto j = 0;
  for (auto score : scores) {
    if (j == 10) break;
    texts_[j]->setText(to_string(j + 1) + "\u00ba " + score->name + " " +
                       to_string(score->score) + " " + to_string(score->time));
    j++;
  }
  for (auto i = scores.size(); i < 10; i++) {
    texts_[i]->setText(to_string(i + 1) + "\u00ba ------ ------ ------");
  }
}

// Defines the render behaviour
void ScoreBoard::render() const {
  // Render the first 10 elements
  for (auto text : texts_) {
    text->render();
  }
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &ScoreBoard::deserialize(std::istream &out) { return out; }

// Defines the serialize method behaviour to save the data into a file save
std::ostream &ScoreBoard::serialize(std::ostream &is) const { return is; }
