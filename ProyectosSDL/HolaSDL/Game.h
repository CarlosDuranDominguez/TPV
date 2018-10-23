#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include "Ball.h"
#include "Paddle.h"
#include "BlocksMap.h"
#include "Wall.h"

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 3;
const uint FRAMERATE = 30;
const uint NUMBER_TEXTURES = 5;
const double PADDLESPEED = 5; 

enum Textures { BALL, BRICKS, PADDLE, SIDE, TOPSIDE };

struct TextureInfo {
	string path;
	uint columns;
	uint rows;
};

const TextureInfo TEXTURES[5]{
	TextureInfo{"../images/ball.png",1,1},
	TextureInfo{"../images/bricks.png",3,2},
	TextureInfo{"../images/paddle.png",1,1},
	TextureInfo{"../images/side.png",1,1},
	TextureInfo{"../images/topside.png",1,1},
};

const string LEVEL[3]{ "../levels/level01.ark","../levels/level02.ark","../levels/level03.ark" };

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false, gameover = false, win = false;
	Texture* textures[NUMBER_TEXTURES];
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	BlocksMap* blocksmap = nullptr;
	Wall *upWall = nullptr, *rightWall = nullptr, *leftWall = nullptr;
public:
	Game();
	~Game();
	void run();
	void render() const;
	void update();
	void handleEvents();
	void collides();
};

