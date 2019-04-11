#pragma once
#include <string>
#include <vector>

struct PlayerGame {
  std::string name;
  int score;
  int time;
};

class TopBoard {
  std::vector<PlayerGame *> scores_;
  bool static compareName(const PlayerGame *game1, const PlayerGame *game2);
  bool static compareScore(const PlayerGame *, const PlayerGame *);
  bool static compareTime(const PlayerGame *, const PlayerGame *);

 public:
  TopBoard();
  TopBoard(const std::string &path);
  ~TopBoard();
  void loadFile(const std::string &path);
  void storeFile(const std::string &path);
  void sortByName();
  void sortByScore();
  void sortByTime();
  void pushScore(PlayerGame *game);
  std::vector<PlayerGame *> showScores() const;
};

std::ostream &operator<<(std::ostream &os, const PlayerGame &v);
std::istream &operator>>(std::istream &os, PlayerGame &v);
