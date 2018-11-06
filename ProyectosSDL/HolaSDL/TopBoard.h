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
class TopBoard {
private:
	Font* font;
	string filename;
	std::vector<PlayerGame> allGames; 
	Vector2D position;
	int width, height;
	SDL_Color color;
	bool static _sortByName(const PlayerGame& game1, const PlayerGame& game2);
	bool static _sortByScore(PlayerGame&, PlayerGame&);
	bool static _sortByTime(PlayerGame&, PlayerGame&);
	void _reWrite();
public:
	TopBoard(Font* font, double x, double y, int width, int height, SDL_Color color, string filename);
	~TopBoard();
	void pushGame(PlayerGame newGame);
	void sortByName();
	void sortByScore();
	void sortByTime();
	void render() const;
	
};
ostream& operator << (ostream& os, const PlayerGame& v)
{
	return os << v.name <<' '<<v.score<<' '<<v.time;
}

istream& operator>> (istream& os, PlayerGame& v)
{
	return os >> v.name >> v.score >> v.time;
}