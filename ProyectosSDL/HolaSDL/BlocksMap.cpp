#include "BlocksMap.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <fstream>

BlocksMap::BlocksMap(int padding)
{
	_mapWidth = WIN_WIDTH - 2 * padding;
	_mapHeight = WIN_HEIGHT / 2 - padding;
}

BlocksMap::BlocksMap(string path, int padding, Texture *texture)
{
	_mapWidth = WIN_WIDTH - 2 * padding;
	_mapHeight = WIN_HEIGHT / 2 - padding;
	loadMap(path, padding, texture);
}

BlocksMap::~BlocksMap()
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			if (_blocks[i][j] != nullptr)
			{
				delete _blocks[i][j];
			}
		}
		delete[] _blocks[i];
	}
	delete[] _blocks;
}

void BlocksMap::loadMap(string path, int padding, Texture *texture)
{

	ifstream file;
	file.open(path);
	if (file.good())
	{
		_numberOfBlocks = 0;
		file >> _rows >> _columns;
		_blocks = new Block **[_rows];
		_cellWidth = _mapWidth / _columns;
		_cellHeight = _mapHeight / _rows;
		int aux;
		for (int i = 0; i < _rows; i++)
		{
			_blocks[i] = new Block *[_columns];
			for (int j = 0; j < _columns; j++)
			{
				file >> aux;
				if (aux != 0)
				{
					_blocks[i][j] = new Block(padding + j * _cellWidth, padding + i * _cellHeight, _cellWidth, _cellHeight, i, j, aux - 1, texture);
					_numberOfBlocks++;
				}
				else
				{
					_blocks[i][j] = nullptr;
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

void BlocksMap::render() const
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			if (_blocks[i][j] != nullptr)
			{
				_blocks[i][j]->render();
			}
		}
	}
}

int BlocksMap::numberOfBlocks() const
{
	return _numberOfBlocks;
}

bool BlocksMap::collide(const Ball *object, Vector2D &collisionPosition, Vector2D &reflection)
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			if (_blocks[i][j] != nullptr && _blocks[i][j]->collide(object, collisionPosition, reflection))
			{
				_numberOfBlocks--;
				delete _blocks[i][j];
				_blocks[i][j] = nullptr;
				return true;
			}
		}
	}
	return false;
}
