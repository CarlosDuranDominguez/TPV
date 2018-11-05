#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
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
const uint NUMBER_FONTS = 15;
const double PADDLESPEED = 5; 

enum Textures { BALL, BRICKS, PADDLE, SIDE, TOPSIDE };
enum FontsStyles {BOLD,BOLDITALIC,DEMIBOLD,DEMIBOLDITALIC,EXTRALIGHT,HEAVY,HEAVYITALIC,LIGHT,LIGHTITALIC,MEDIUM,MEDIUMITALIC,REGULAR,REGULARITALIC,STENCIL};
struct TextureInfo {
	string path;
	uint columns;
	uint rows;
};

const TextureInfo TEXTURES[NUMBER_TEXTURES] {
	TextureInfo{"../images/ball.png",1,1},
	TextureInfo{"../images/bricks.png",3,2},
	TextureInfo{"../images/paddle.png",1,1},
	TextureInfo{"../images/side.png",1,1},
	TextureInfo{"../images/topside.png",1,1},
};
const string FONTSDIRECTORIES[NUMBER_FONTS]{
	"../fonts/Oswald-Bold.tff",
	"../fonts/Oswald-BoldItalic.tff",
	"../fonts/Oswald-DemiBold.tff",
	"../fonts/Oswald-Demi-BoldItalic.tff",
	"../fonts/Oswald-ExtraLight.tff",
	"../fonts/Oswald-Extra-LightItalic.tff",
	"../fonts/Oswald-Heavy.tff",
	"../fonts/Oswald-HeavyItalic.tff",
	"../fonts/Oswald-Light.tff",
	"../fonts/Oswald-LightItalic.tff",
	"../fonts/Oswald-Medium.tff",
	"../fonts/Oswald-MediumItalic.tff",
	"../fonts/Oswald-Regular.tff",
	"../fonts/Oswald-RegularItalic.tff",
	"../fonts/Oswald-Stencil.tff"
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
	bool collides(const Ball*, Vector2D&, Vector2D&);
};

