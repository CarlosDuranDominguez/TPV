#pragma once
#include "checkML.h"
#include <string>
#include <vector>
#include <iostream>


struct PlayerGame
{
	std::string name;
	int score;
	int time;
};

class TopBoard {
private:
	std::vector<PlayerGame*> _scores;
	bool static _comparename(const PlayerGame*game1, const PlayerGame *game2);
	bool static _comparescore(const PlayerGame *, const PlayerGame *);
	bool static _comparetime(const PlayerGame *, const PlayerGame *);
public:
	TopBoard();
	TopBoard(const std::string& path);
	~TopBoard();
	void loadFile(const std::string& path);
	void storeFile(const std::string& path);
	void sortByName();
	void sortByScore();
	void sortByTime();
	void pushScore(PlayerGame* game);
	std::vector<PlayerGame*> showScores() const;
};

std::ostream &operator<<(std::ostream &os, const PlayerGame &v);

std::istream &operator>>(std::istream &os, PlayerGame &v);