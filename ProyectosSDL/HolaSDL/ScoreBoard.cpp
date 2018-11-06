#include "ScoreBoard.h"
#include <fstream>
#include <iostream>

ScoreBoard::ScoreBoard(Font *font, double x, double y, int width, int height, SDL_Color color, string filename) : font(font), position(x, y), width(width), height(height), color(color), filename(filename)
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
			allGames.reserve(numberOfGames);
			while (!file.eof() && i < numberOfGames)
			{
				file >> tmp;
				allGames.push_back(tmp);
				i++;
			}
			file.close();
			if (i == numberOfGames)
			{
				for (unsigned int j = 0; j < allGames.size(); j++)
				{
					string aux = to_string(j + 1) + "\u00ba " + allGames[j].name + " " + to_string(allGames[j].score) + " " + to_string(allGames[j].time);
					texts[j] = new Text(font, position + Vector2D(0, height) * j, width, height, color, aux);
				}
				for (unsigned int j = allGames.size(); j < 10; j++)
				{
					string aux = to_string(j + 1) + "\u00ba ------ ------ ------";
					texts[j] = new Text(font, position + Vector2D(0, height) * j, width, height, color, aux);
				}
				return;
			}
		}
	}
	throw "Error loading scoreboard";
}

ScoreBoard::~ScoreBoard()
{
	fstream file;
	file.open(filename, fstream::out);
	file << allGames.size() << '\n';
	for
		each(PlayerGame var in allGames)
		{
			file << var << '\n';
		}
	file.close();
	for (unsigned int j = 0; j < 10; j++)
	{
		delete texts[j];
	}
}

bool ScoreBoard::compareName(const PlayerGame &game1, const PlayerGame &game2)
{
	return game1.name < game2.name;
}

bool ScoreBoard::compareScore(const PlayerGame &game1, const PlayerGame &game2)
{
	return game1.score < game2.score;
}

bool ScoreBoard::compareTime(const PlayerGame &game1, const PlayerGame &game2)
{
	return game1.time > game2.time;
}

void ScoreBoard::pushGame(PlayerGame newGame)
{
	allGames.push_back(newGame);
	sortByName();
}

void ScoreBoard::sortByName()
{
	sort(allGames.begin(), allGames.end(), compareName);
	_rewrite();
}

void ScoreBoard::sortByScore()
{
	sort(allGames.begin(), allGames.end(), compareScore);
	_rewrite();
}

void ScoreBoard::sortByTime()
{
	sort(allGames.begin(), allGames.end(), compareTime);
	_rewrite();
}

void ScoreBoard::_rewrite()
{
	for (unsigned int j = 0; j < allGames.size(); j++)
	{
		string aux = to_string(j + 1) + "\u00ba " + allGames[j].name + " " + to_string(allGames[j].score) + " " + to_string(allGames[j].time);
		texts[j]->setText(aux);
		texts[j]->setPosition(position + Vector2D(0, height) * j);
	}
	for (unsigned int j = allGames.size(); j < 10; j++)
	{
		string aux = to_string(j + 1) + "\u00ba ------ ------ ------";
		texts[j]->setText(aux);
		texts[j]->setPosition(position + Vector2D(0, height) * j);
	}
}

void ScoreBoard::render() const
{
	for (unsigned int j = 0; j < 10; j++)
	{
		texts[j]->render();
	}
}

ostream &operator<<(ostream &os, const PlayerGame &v)
{
	return os << v.name << ' ' << v.score << ' ' << v.time;
}

istream &operator>>(istream &os, PlayerGame &v)
{
	return os >> v.name >> v.score >> v.time;
}
