#include"TopBoard.h"
#include <fstream>
#include <iostream>

bool TopBoard::_sortByName(PlayerGame& game1, PlayerGame& game2) {
	return game1.name < game2.name;
}
bool TopBoard::_sortByScore(PlayerGame& game1, PlayerGame& game2) {
	return game1.score < game2.score;
}
bool TopBoard::_sortByTime(PlayerGame& game1, PlayerGame& game2) {
	return game1.time > game2.time;
}
TopBoard::TopBoard(Font* font, string filename = "../save/save.save", double x, double y, int width, int height, SDL_Color color) :
	font(font), position(x, y), width(width), height(height), color(color), filename(filename) {
	fstream file;
	file.open(filename, fstream::in | fstream::out);
	int numberOfGames;
	if (!file.eof()) {
		file >> numberOfGames;
		if (numberOfGames >= 0) {
			int i = 0;
			PlayerGame tmp;
			allGames.reserve(numberOfGames);
			while (!file.eof() && i < numberOfGames) {
				file >> tmp;
				allGames.push_back(tmp);
				i++;
			}
			file.close();
			if (i == numberOfGames) {
				for(int j = 0; j <allGames.size(); j++)
				{
					string aux = to_string(j)+"º "+allGames[j].name+" "+to_string(allGames[j].score)+" " + to_string(allGames[j].time);
					allGames[j].text = new Text(font, position + Vector2D(0, height)*j, width, height, color, aux);
				}
				return;
			}
		}
	}
	throw "Error loading scoreboard";
}
TopBoard::~TopBoard() {
	fstream file;
	file.open(filename, fstream::out);
	file << allGames.size() << '\n';
	for each (PlayerGame var in allGames)
	{
		file << var << '\n';
	}
	file.close();
	for each (PlayerGame game in allGames)
	{
		delete game.text;
	}
}
void TopBoard::pushGame(PlayerGame newGame) {
	newGame.text = new Text(font, Vector2D(), width, height, color, "");
	allGames.push_back(newGame);
	sortByName();
}

void TopBoard::sortByName() {
	sort(allGames.begin(), allGames.end(), _sortByName);
	_reWrite();
}

void TopBoard::sortByScore() {
	sort(allGames.begin(), allGames.end(), _sortByScore);
	_reWrite();
}

void TopBoard::sortByTime() {
	sort(allGames.begin(), allGames.end(), _sortByTime);
	_reWrite();
}

void TopBoard::_reWrite() {
	for (int j = 0; j < allGames.size(); j++)
	{
		string aux = to_string(j) + "º " + allGames[j].name + " " + to_string(allGames[j].score) + " " + to_string(allGames[j].time);
		allGames[j].text->setText(aux);
		allGames[j].text->setPosition(position + Vector2D(0, height)*j);
	}
}

void TopBoard::render() const {
	for each (PlayerGame game in allGames)
	{
		game.text->render();
	}
}