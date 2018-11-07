#include "ScoreBoard.h"
#include <fstream>
#include <iostream>

/*
 * Constructor.
 */
ScoreBoard::ScoreBoard(Font *font, double x, double y, int width, int height, SDL_Color color, string filename) : _font(font), _position(x, y), _width(width), _height(height), _color(color), _filename(filename)
{
	fstream file;
	file.open(filename, fstream::in | fstream::out);
	int numberOfGames;
	if (!file.eof())
	{
		file >> numberOfGames;
		if (numberOfGames >= 0)
		{
			int i = 0;
			PlayerGame tmp;
			_allGames.reserve(numberOfGames);
			while (!file.eof() && i < numberOfGames)
			{
				file >> tmp;
				_allGames.push_back(tmp);
				i++;
			}
			file.close();
			if (i == numberOfGames)
			{
				for (unsigned int j = 0; j < _allGames.size() && j < 10; j++)
				{
					string aux = to_string(j + 1) + "\u00ba " + _allGames[j].name + " " + to_string(_allGames[j].score) + " " + to_string(_allGames[j].time);
					_texts[j] = new Text(font, _position + Vector2D(0, height) * j, width, height, color, aux);
				}
				for (unsigned int j = _allGames.size(); j < 10; j++)
				{
					string aux = to_string(j + 1) + "\u00ba ------ ------ ------";
					_texts[j] = new Text(font, _position + Vector2D(0, height) * j, width, height, color, aux);
				}
				return;
			}
		}
	}
	throw "Error loading scoreboard";
}

/*
 * Destructor.
 */
ScoreBoard::~ScoreBoard()
{
	fstream file;
	file.open(_filename, fstream::out);
	file << _allGames.size() << '\n';
	for each(PlayerGame var in _allGames)
	{
		file << var << '\n';
	}
	file.close();
	for (unsigned int j = 0; j < 10; j++)
	{
		delete _texts[j];
	}
}

/*
 * The comparing function depending on the player's name.
 */
bool ScoreBoard::_comparename(const PlayerGame &game1, const PlayerGame &game2)
{
	return game1.name < game2.name;
}

/*
 * The comparing function depending on the player's score.
 */
bool ScoreBoard::_comparescore(const PlayerGame &game1, const PlayerGame &game2)
{
	return game1.score < game2.score;
}

/*
 * The comparing function depending on the player's time.
 */
bool ScoreBoard::_comparetime(const PlayerGame &game1, const PlayerGame &game2)
{
	return game1.time > game2.time;
}

/*
 * It puts a new finish game.
 */
void ScoreBoard::pushGame(const PlayerGame& newGame)
{
	_allGames.push_back(newGame);
	sortByName();
}

/*
 * It sorts the scoreboard depending on the name.
 */
void ScoreBoard::sortByName()
{
	sort(_allGames.begin(), _allGames.end(), _comparename);
	_rewrite();
}

/*
 * It sorts the scoreboard depending on the score.
 */
void ScoreBoard::sortByScore()
{
	sort(_allGames.begin(), _allGames.end(), _comparescore);
	_rewrite();
}

/*
 * It sorts the scoreboard depending on the time.
 */
void ScoreBoard::sortByTime()
{
	sort(_allGames.begin(), _allGames.end(), _comparetime);
	_rewrite();
}

/*
 * It creates the first ten games.
 */
void ScoreBoard::_rewrite()
{
	for (unsigned int j = 0; j < _allGames.size() && j < 10; j++)
	{
		string aux = to_string(j + 1) + "\u00ba " + _allGames[j].name + " " + to_string(_allGames[j].score) + " " + to_string(_allGames[j].time);
		_texts[j]->setText(aux);
		_texts[j]->setPosition(_position + Vector2D(0, _height) * j);
	}
	for (unsigned int j = _allGames.size(); j < 10; j++)
	{
		string aux = to_string(j + 1) + "\u00ba ------ ------ ------";
		_texts[j]->setPosition(_position + Vector2D(0, _height) * j);
	}
}

/*
 * It renders the first ten score's games.
 */
void ScoreBoard::render() const
{
	for (unsigned int j = 0; j < 10; j++)
	{
		_texts[j]->render();
	}
}

/*
 * It inserts the the PlayerGamer on a stream.
 */
ostream &operator<<(ostream &os, const PlayerGame &v)
{
	return os << v.name << ' ' << v.score << ' ' << v.time;
}

/*
 * It reads a Player game from the stream.
 */
istream &operator>>(istream &os, PlayerGame &v)
{
	return os >> v.name >> v.score >> v.time;
}
