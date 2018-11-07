#pragma once

#include "checkML.h"
#include <vector>
#include <string>
#include "Font.h"
#include "Text.h"
#include <algorithm>

struct PlayerGame
{
	std::string name;
	int score;
	int time;
};

class ScoreBoard
{
private:
	Font *_font;
	string _filename;
	std::vector<PlayerGame> _allGames;
	Text *_texts[10];
	Vector2D _position;
	int _width, _height;
	SDL_Color _color;
	bool static _comparename(const PlayerGame &game1, const PlayerGame &game2);
	bool static _comparescore(const PlayerGame &, const PlayerGame &);
	bool static _comparetime(const PlayerGame &, const PlayerGame &);
	void _rewrite();

public:
	ScoreBoard(Font *font, double x, double y, int width, int height, SDL_Color color, string filename);
	~ScoreBoard();
	void pushGame(const PlayerGame& newGame);
	void sortByName();
	void sortByScore();
	void sortByTime();
	void render() const;
};

ostream &operator<<(ostream &os, const PlayerGame &v);

istream &operator>>(istream &os, PlayerGame &v);
