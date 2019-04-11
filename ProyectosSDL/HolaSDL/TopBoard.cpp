#include "TopBoard.h"
#include <algorithm>
#include <fstream>

/// Public
// Constructor
TopBoard::TopBoard(const std::string &path) : _scores() {
  loadFile(path);
  sortByScore();
}

/// Public
// Destructor
TopBoard::~TopBoard() {
  for (auto score : _scores) {
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
      _scores.push_back(game);
    }
  }
  file.close();
}

/// Public
// Stores the current top leaderboard to a file
void TopBoard::storeFile(const std::string &path) {
  std::ofstream file;
  file.open(path, std::ofstream::in);
  for (auto game : _scores) {
    file << *game << "\n";
  }
  file.close();
}

/// Public
// Sorts the top leaderboard by name
void TopBoard::sortByName() {
  sort(_scores.begin(), _scores.end(), _comparename);
}

/// Public
// Sorts the top leaderboard by the amount of points
void TopBoard::sortByScore() {
  sort(_scores.begin(), _scores.end(), _comparescore);
}

/// Public
// Sorts the top leaderboard by the amount of seconds
void TopBoard::sortByTime() {
  sort(_scores.begin(), _scores.end(), _comparetime);
}

/// Public
// Adds a new line to the leaderboard
void TopBoard::pushScore(PlayerGame *game) {
  _scores.push_back(game);
  sortByName();
}

/// Public
// Gets the scores
std::vector<PlayerGame *> TopBoard::showScores() const { return _scores; }

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
bool TopBoard::_comparename(const PlayerGame *game1, const PlayerGame *game2) {
  return game1->name < game2->name;
}

/// Private
// The comparing function depending on the player's score
bool TopBoard::_comparescore(const PlayerGame *game1, const PlayerGame *game2) {
  return game1->score > game2->score;
}

/// Private
// The comparing function depending on the player's time
bool TopBoard::_comparetime(const PlayerGame *game1, const PlayerGame *game2) {
  return game1->time < game2->time;
}
