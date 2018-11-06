#pragma once

#include <vector>
#include <string>
#include "Font.h"
#include "Text.h"
#include <algorithm>

struct PlayerGame{
	std::string name;
	int score;
	int time;
	Text* text;
};

class ScoreBoard {
private:
	Font* font;
	string filename;
	std::vector<PlayerGame> allGames; 
	Vector2D position;
	int width, height;
	SDL_Color color;
	bool static compareName(const PlayerGame& game1, const PlayerGame& game2);
	bool static compareScore(const PlayerGame&, const PlayerGame&);
	bool static compareTime(const PlayerGame&, const PlayerGame&);
	void _rewrite();
public:
	ScoreBoard(Font* font, double x, double y, int width, int height, SDL_Color color, string filename);
	~ScoreBoard();
	void pushGame(PlayerGame newGame);
	void sortByName();
	void sortByScore();
	void sortByTime();
	void render() const;
	
};

ostream& operator << (ostream& os, const PlayerGame& v);

istream& operator>> (istream& os, PlayerGame& v);