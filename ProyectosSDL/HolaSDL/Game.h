#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "checkML.h"
#include "Texture.h"
#include "Font.h"
#include "GameManager.h"
#include "StateManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "ScoreBoardState.h"

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 3;
const uint FRAMERATE = 30;
const uint NUMBER_TEXTURES = 5;
const uint NUMBER_FONT_STYLES = 15;
const double PADDLESPEED = 5;

enum Textures
{
	BALL,
	BRICKS,
	PADDLE,
	SIDE,
	TOPSIDE
};

enum FontsStyles
{
	BOLD,
	BOLDITALIC,
	DEMIBOLD,
	DEMIBOLDITALIC,
	EXTRALIGHT,
	EXTRALIGHTITALIC,
	HEAVY,
	HEAVYITALIC,
	LIGHT,
	LIGHTITALIC,
	MEDIUM,
	MEDIUMITALIC,
	REGULAR,
	REGULARITALIC,
	STENCIL
};

struct TextureInfo
{
	string path;
	uint columns;
	uint rows;
};

const TextureInfo TEXTURES[NUMBER_TEXTURES] {
	TextureInfo{"../images/ball.png", 1, 1},
	TextureInfo{"../images/bricks.png", 3, 2},
	TextureInfo{"../images/paddle.png", 1, 1},
	TextureInfo{"../images/side.png", 1, 1},
	TextureInfo{"../images/topside.png", 1, 1},
};

const string FONTSDIRECTORIES[NUMBER_FONT_STYLES] {
	"../fonts/Oswald-Bold.ttf",
	"../fonts/Oswald-BoldItalic.ttf",
	"../fonts/Oswald-DemiBold.ttf",
	"../fonts/Oswald-Demi-BoldItalic.ttf",
	"../fonts/Oswald-ExtraLight.ttf",
	"../fonts/Oswald-Extra-LightItalic.ttf",
	"../fonts/Oswald-Heavy.ttf",
	"../fonts/Oswald-HeavyItalic.ttf",
	"../fonts/Oswald-Light.ttf",
	"../fonts/Oswald-LightItalic.ttf",
	"../fonts/Oswald-Medium.ttf",
	"../fonts/Oswald-MediumItalic.ttf",
	"../fonts/Oswald-Regular.ttf",
	"../fonts/Oswald-RegularItalic.ttf",
	"../fonts/Oswald-Stencil.ttf"
};

const string LEVEL[3] {
	"../levels/level01.ark",
	"../levels/level02.ark",
	"../levels/level03.ark"
};

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color GREY = { 80, 80, 80, 255 };

class Game
{
private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	Texture *textures[NUMBER_TEXTURES];
	Font *fonts[1];
	GameManager *gamemanager;
	StateManager *statemanager;
	GameState *game;
	MenuState *menu;
	ScoreBoardState *scoreboard;

public:
	Game();
	~Game();
	Texture **getTextures();
	Font **getFonts();
	void changeState(string stateName);
	void run();
};
