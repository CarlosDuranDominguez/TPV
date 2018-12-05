#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "checkML.h"
#include "Texture.h"
#include "Font.h"
#include "GameManager.h"
#include "State.h"
#include "GameState.h"
#include <map>
#include "ArkanoidSettings.h"

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUMBER_TEXTURES = 44;
const uint NUMBER_FONT_STYLES = 15;
const float32 PADDLESPEED = 5;

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

enum Textures
{
  BALL,
  BRICKS,
  PADDLE,
  SIDE,
  TOPSIDE,
  ENEMY1,
  ENEMY2,
  ENEMY3,
  ENEMY4,
  ENEMY5,
  ENEMY6,
  REWARD1,
  REWARD2,
  REWARD3,
  REWARD4,
  REWARD5,
  REWARD6,
  REWARD7,
  REWARD8,
  REWARD9,
  REWARD10,
  REWARD11,
  REWARD12,
  REWARD13,
  REWARD14,
  REWARD15,
  REWARD16,
  REWARD17,
  REWARD18,
  REWARD19,
  LIFE,
  ILUMINATION1,
  ILUMINATION2,
  ILUMINATION3,
  ILUMINATION4,
  ILUMINATION5,
  ILUMINATION6,
  ILUMINATION7,
  ILUMINATION8,
  ILUMINATION9,
  ILUMINATION10,
  BALLBLACK,
  BALLCOLOURS,
  BALLON
};

const TextureInfo TEXTURES[NUMBER_TEXTURES]{
    TextureInfo{"../images/ball.png", 1, 1},
    TextureInfo{"../images/bricks.png", 3, 2},
    TextureInfo{"../images/paddle.png", 1, 1},
    TextureInfo{"../images/side.png", 1, 1},
    TextureInfo{"../images/topside.png", 1, 1},
    TextureInfo{"../images/Enemy01.png", 25, 1},
    TextureInfo{"../images/Enemy02.png", 25, 1},
    TextureInfo{"../images/Enemy03.png", 25, 1},
    TextureInfo{"../images/Enemy04.png", 25, 1},
    TextureInfo{"../images/Enemy05.png", 25, 1},
    TextureInfo{"../images/Enemy06.png", 25, 1},
    TextureInfo{"../images/Reward01.png", 8, 1},
    TextureInfo{"../images/Reward02.png", 8, 1},
    TextureInfo{"../images/Reward03.png", 8, 1},
    TextureInfo{"../images/Reward04.png", 8, 1},
    TextureInfo{"../images/Reward05.png", 8, 1},
    TextureInfo{"../images/Reward06.png", 8, 1},
    TextureInfo{"../images/Reward07.png", 8, 1},
    TextureInfo{"../images/Reward08.png", 8, 1},
    TextureInfo{"../images/Reward09.png", 8, 1},
    TextureInfo{"../images/Reward10.png", 8, 1},
    TextureInfo{"../images/Reward11.png", 8, 1},
    TextureInfo{"../images/Reward12.png", 8, 1},
    TextureInfo{"../images/Reward13.png", 8, 1},
    TextureInfo{"../images/Reward14.png", 8, 1},
    TextureInfo{"../images/Reward15.png", 8, 1},
    TextureInfo{"../images/Reward16.png", 8, 1},
    TextureInfo{"../images/Reward17.png", 8, 1},
    TextureInfo{"../images/Reward18.png", 8, 1},
    TextureInfo{"../images/Reward19.png", 8, 1},
    TextureInfo{"../images/Life.png", 1, 1},
    TextureInfo{"../images/Illumination01.png", 1, 6},
    TextureInfo{"../images/Illumination02.png", 1, 6},
    TextureInfo{"../images/Illumination03.png", 1, 6},
    TextureInfo{"../images/Illumination04.png", 1, 6},
    TextureInfo{"../images/Illumination05.png", 1, 6},
    TextureInfo{"../images/Illumination06.png", 1, 6},
    TextureInfo{"../images/Illumination07.png", 1, 6},
    TextureInfo{"../images/Illumination08.png", 1, 6},
    TextureInfo{"../images/Illumination09.png", 1, 6},
    TextureInfo{"../images/Illumination10.png", 1, 6},
    TextureInfo{"../images/BallBlack.png", 1, 1},
    TextureInfo{"../images/BallColours.png", 3, 1},
    TextureInfo{"../images/Ballon.png", 2, 1}};

const string FONTSDIRECTORIES[NUMBER_FONT_STYLES]{
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
    "../fonts/Oswald-Stencil.ttf"};

const string LEVEL[3]{
    "../levels/level01.ark",
    "../levels/level02.ark",
    "../levels/level03.ark"};

enum Fonts
{
  BIGFONT,
  MEDIUMFONT
};

const uint NUMBERFONTS = 2;

const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color GREY = {80, 80, 80, 255};

enum States
{
  GAMEOVER,
  SCOREBOARD,
  GAME,
  MENU
};

class Game
{
private:
  SDL_Window *_window = nullptr;
  SDL_Renderer *_renderer = nullptr;
  Texture *_textures[NUMBER_TEXTURES];
  Font *_fonts[NUMBERFONTS];
  static GameManager *_gamemanager;
  map<States, State *> _states;
  States _state = States::GAME;
  static b2World *_world;

public:
  Game();
  ~Game();
  static Game *current;
  Texture **getTextures();
  Font **getFonts();
  void changeState(const States &state);
  void newScore(const string &name, int score, float32 time);
  void run();
  States getState() { return _state; };
  GameState *getGameState() { return dynamic_cast<GameState *>(_states[GAME]); }
  static GameManager *getGameManager();
  static b2World *getWorld();
  static void setWorld(b2World &world);
};
