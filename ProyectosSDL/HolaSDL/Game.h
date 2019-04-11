#pragma once

#include <map>
#include "Font.h"
#include "GameManager.h"
#include "GameState.h"
#include "SDL.h"
#include "State.h"
#include "Texture.h"

const Uint32 kWinWidth = 800;
const Uint32 kWinHeight = 600;
const Uint32 kNumberTextures = 44;
const Uint32 kNumberFontStyles = 15;
const float32 kPaddleSpeed = 5;

enum FontsStyles {
  BOLD,
  BOLD_ITALIC,
  DEMIBOLD,
  DEMIBOLD_ITALIC,
  EXTRA_LIGHT,
  EXTRA_LIGHT_ITALIC,
  HEAVY,
  HEAVY_ITALIC,
  LIGHT,
  LIGHT_ITALIC,
  MEDIUM,
  MEDIUM_ITALIC,
  REGULAR,
  REGULAR_ITALIC,
  STENCIL
};

struct TextureInfo {
  string path;
  Uint32 columns;
  Uint32 rows;
};

enum Textures {
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

const TextureInfo kTextures[kNumberTextures]{
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

const string kFontsdirectories[kNumberFontStyles]{
    "../fonts/Oswald-Bold.ttf",       "../fonts/Oswald-BoldItalic.ttf",
    "../fonts/Oswald-DemiBold.ttf",   "../fonts/Oswald-Demi-BoldItalic.ttf",
    "../fonts/Oswald-ExtraLight.ttf", "../fonts/Oswald-Extra-LightItalic.ttf",
    "../fonts/Oswald-Heavy.ttf",      "../fonts/Oswald-HeavyItalic.ttf",
    "../fonts/Oswald-Light.ttf",      "../fonts/Oswald-LightItalic.ttf",
    "../fonts/Oswald-Medium.ttf",     "../fonts/Oswald-MediumItalic.ttf",
    "../fonts/Oswald-Regular.ttf",    "../fonts/Oswald-RegularItalic.ttf",
    "../fonts/Oswald-Stencil.ttf"};

const string kLevel[3]{"../levels/level01.ark", "../levels/level02.ark",
                       "../levels/level03.ark"};

enum Fonts { BIG_FONT, MEDIUM_FONT };

const Uint32 kNumberFonts = 2;

const SDL_Color kWhite = {255, 255, 255, 255};
const SDL_Color kGrey = {80, 80, 80, 255};

enum States { GAMEOVER, SCOREBOARD, GAME, MENU };

class Game {
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  Texture *textures_[kNumberTextures];
  Font *fonts_[kNumberFonts];
  static GameManager *gameManager_;
  map<States, State *> states_;
  States state_ = MENU;
  static b2World *world_;

 public:
  Game();
  ~Game();
  static Game *current_;
  Texture **getTextures();
  Font **getFonts();
  void changeState(const States &state);
  void run();
  States getState();
  GameState *getGameState();
  static GameManager *getGameManager();
  static b2World *getWorld();
  static void setWorld(b2World &world);
};
