#include "ScoreBoard.h"
#include <fstream>
#include <iostream>
#include "Game.h"

/// Public
// Constructor
ScoreBoard::ScoreBoard(Font *font, float32 x, float32 y, float32 width,
                       float32 height, SDL_Color color)
    : GameObject(x, y, width, height), font_(font), color_(color) {
  vector<PlayerGame *> scores = Game::getGameManager()->getScores();
  int j = 0;
  for (auto score : scores) {
    if (j == 10) break;
    texts_[j] =
        new Text(font_, position_.x, position_.y + getSize().y * j, getSize().x,
                 getSize().y, color_,
                 to_string(j + 1) + "\u00ba " + score->name + " " +
                     to_string(score->score) + " " + to_string(score->time));
    j++;
  }
  for (unsigned int j = scores.size(); j < 10; j++) {
    string aux = to_string(j + 1) + "\u00ba ------ ------ ------";
    texts_[j] = new Text(font_, position_.x, position_.y + getSize().y * j,
                         getSize().x, getSize().y, color_, aux);
  }
}

/// Public
// Destructor
ScoreBoard::~ScoreBoard() {
  for (auto text : texts_) {
    delete text;
  }
}

/// Public
// Creates the first ten games.
void ScoreBoard::rewrite() {
  vector<PlayerGame *> scores = Game::getGameManager()->getScores();
  int j = 0;
  for (auto score : scores) {
    if (j == 10) break;
    texts_[j]->setText(to_string(j + 1) + "\u00ba " + score->name + " " +
                       to_string(score->score) + " " + to_string(score->time));
    j++;
  }
  for (unsigned int j = scores.size(); j < 10; j++) {
    texts_[j]->setText(to_string(j + 1) + "\u00ba ------ ------ ------");
  }
}

/// Public Virtual
// Defines the render behaviour
void ScoreBoard::render() const {
  // Render the first 10 elements
  for (unsigned int j = 0; j < 10; j++) {
    texts_[j]->render();
  }
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &ScoreBoard::deserialize(std::istream &out) { return out; }

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &ScoreBoard::serialize(std::ostream &is) const { return is; }
