#include "BlocksMap.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <fstream>

BlocksMap::BlocksMap(string path, int padding, Texture* texture)
{
	mapWidth = WIN_WIDTH-2*padding;
	mapHeight = WIN_HEIGHT/2-padding;
	loadMap(path, padding, texture);
}

BlocksMap::~BlocksMap() 
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (blocks[i][j] != nullptr)
			{
				delete blocks[i][j];
			}
		}
		delete[] blocks[i];
	}
	delete[] blocks;
}

void BlocksMap::loadMap(string path, int padding, Texture* texture)
{
	ifstream file;
	file.open(path);
	if (file.good())
	{
		file >> rows >> columns;
		blocks = new Block**[rows];
		cellWidth = mapWidth / columns;
		cellHeight = mapHeight / rows;
		int aux;
		for (int i = 0; i < rows; i++) {
			blocks[i] = new Block*[columns];
			for (int j = 0; j < columns; j++) {
				file >> aux;
				if (aux != 0)
				{
					blocks[i][j] = new Block(padding + j * cellWidth, padding + i * cellHeight, cellWidth, cellHeight, i, j, aux - 1, texture);
				}
				else
				{
					blocks[i][j] = nullptr;
				}
			}
		}
		file.close();
	} 
	else
	{
		throw "Error loading level from " + path;
	}
}

void BlocksMap::render() 
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (blocks[i][j] != nullptr)
			{
				blocks[i][j]->render();
			}
		}
	}
}

int BlocksMap::numberOfBlocks() 
{
	int ret = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (blocks[i][j] != nullptr)
			{
				ret++;
			}
		}
	}
	return -1;
}

bool BlocksMap::collide(const Ball* object, Vector2D& collisionPosition, Vector2D& reflection) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (blocks[i][j]!=nullptr && blocks[i][j]->collide(object, collisionPosition, reflection))
			{
				blocks[i][j]->~Block();
				blocks[i][j] = nullptr;
				return true;
			}
		}
	}
	return false;
}