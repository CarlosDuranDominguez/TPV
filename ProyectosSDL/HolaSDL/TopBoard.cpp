#include "TopBoard.h"
#include <algorithm>
#include <fstream>

/**
 * The comparing function depending on the player's name.
 */
bool TopBoard::_comparename(const PlayerGame *game1, const PlayerGame *game2)
{
  return game1->name < game2->name;
}

/**
 * The comparing function depending on the player's score.
 */
bool TopBoard::_comparescore(const PlayerGame *game1, const PlayerGame *game2)
{
  return game1->score < game2->score;
}

/**
 * The comparing function depending on the player's time.
 */
bool TopBoard::_comparetime(const PlayerGame *game1, const PlayerGame *game2)
{
  return game1->time > game2->time;
}

TopBoard::TopBoard(const std::string &path) : _scores()
{
  loadFile(path);
}

TopBoard::~TopBoard()
{
  for (auto score : _scores)
  {
    delete score;
  }
}

void TopBoard::loadFile(const std::string &path)
{
  std::ifstream file;
  file.open(path, std::ifstream::out);
  while (!file.eof() && !file.fail())
  {

    PlayerGame *game = new PlayerGame();
    file >> *game;
    if (game->name == "" && game->score == 0 && game->time == 0)
    {
      delete game;
    }
    else
    {
      _scores.push_back(game);
    }
  }
  file.close();
}

void TopBoard::storeFile(const std::string &path)
{
  std::ofstream file;
  file.open(path, std::ofstream::in);
  for (auto game : _scores)
  {
    file << *game << "\n";
  }
  file.close();
}

void TopBoard::sortByName()
{
  sort(_scores.begin(), _scores.end(), _comparename);
}

void TopBoard::sortByScore()
{
  sort(_scores.begin(), _scores.end(), _comparescore);
}

void TopBoard::sortByTime()
{
  sort(_scores.begin(), _scores.end(), _comparetime);
}

void TopBoard::pushScore(PlayerGame *game)
{
  _scores.push_back(game);
  sortByName();
}

std::vector<PlayerGame *> TopBoard::showScores() const
{
  return _scores;
}

/**
 * It inserts the the PlayerGamer on a stream.
 */
std::ostream &operator<<(std::ostream &os, const PlayerGame &v)
{
  return os << v.name << ' ' << v.score << ' ' << v.time;
}

/**
 * It reads a Player game from the stream.
 */
std::istream &operator>>(std::istream &os, PlayerGame &v)
{
  return os >> v.name >> v.score >> v.time;
}
