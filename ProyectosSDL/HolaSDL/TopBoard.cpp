#include "TopBoard.h"
#include <algorithm>
#include <fstream>

/// Public
// Constructor
TopBoard::TopBoard(const std::string &path) : scores_() {
  loadFile(path);
  sortByScore();
}

/// Public
// Destructor
TopBoard::~TopBoard() {
  for (auto score : scores_) {
    delete score;
  }
}

/// Public
// Load top leaderboard from file
void TopBoard::loadFile(const std::string &path) {
  std::ifstream file;
  file.open(path, std::ifstream::out);
  while (!file.eof() && !file.fail()) {
    PlayerGame *game = new PlayerGame();
    file >> *game;
    if (game->name == "" && game->score == 0 && game->time == 0) {
      delete game;
    } else {
      scores_.push_back(game);
    }
  }
  file.close();
}

/// Public
// Stores the current top leaderboard to a file
void TopBoard::storeFile(const std::string &path) {
  std::ofstream file;
  file.open(path, std::ofstream::in);
  for (auto game : scores_) {
    file << *game << "\n";
  }
  file.close();
}

/// Public
// Sorts the top leaderboard by name
void TopBoard::sortByName() {
  sort(scores_.begin(), scores_.end(), compareName);
}

/// Public
// Sorts the top leaderboard by the amount of points
void TopBoard::sortByScore() {
  sort(scores_.begin(), scores_.end(), compareScore);
}

/// Public
// Sorts the top leaderboard by the amount of seconds
void TopBoard::sortByTime() {
  sort(scores_.begin(), scores_.end(), compareTime);
}

/// Public
// Adds a new line to the leaderboard
void TopBoard::pushScore(PlayerGame *game) {
  scores_.push_back(game);
  sortByName();
}

/// Public
// Gets the scores
std::vector<PlayerGame *> TopBoard::showScores() const { return scores_; }

/// Public
// Inserts the PlayerGame on a stream
std::ostream &operator<<(std::ostream &os, const PlayerGame &v) {
  return os << v.name << ' ' << v.score << ' ' << v.time;
}

/// Public
// It reads a Player game from the stream.
std::istream &operator>>(std::istream &os, PlayerGame &v) {
  return os >> v.name >> v.score >> v.time;
}

/// Private
// The comparing function depending on the player's name
bool TopBoard::compareName(const PlayerGame *game1, const PlayerGame *game2) {
  return game1->name < game2->name;
}

/// Private
// The comparing function depending on the player's score
bool TopBoard::compareScore(const PlayerGame *game1, const PlayerGame *game2) {
  return game1->score > game2->score;
}

/// Private
// The comparing function depending on the player's time
bool TopBoard::compareTime(const PlayerGame *game1, const PlayerGame *game2) {
  return game1->time < game2->time;
}

TopBoard::TopBoard() {
}
