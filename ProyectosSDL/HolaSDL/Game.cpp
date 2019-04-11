#include "Game.h"
#include "ArkanoidSettings.h"
#include "GameState.h"
#include "MenuState.h"
#include "SDLError.h"
#include "ScoreBoardState.h"

GameManager *Game::gameManager_ = nullptr;
b2World *Game::world_ = nullptr;
Game *Game::current_ = nullptr;

/// Public
// Constructor
Game::Game() : window_(nullptr), renderer_(nullptr) {
  // Set up the Arkanoid settings for the window's width and height
  ArkanoidSettings::setUp(kWinWidth, kWinHeight);
  current_ = this;

  // Initialize SDL and TTF
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw new SDLError("Error initializing SDL");
  if (TTF_Init() < 0) throw new SDLError("Error loading the SDL font");

  // Create the window and renderer
  window_ = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, kWinWidth, kWinHeight,
                             SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  // If window or renderer is a null pointer, throw a SDLError
  if (window_ == nullptr || renderer_ == nullptr)
    throw new SDLError("Error loading the SDL window or renderer");

  // Create the textures
  for (Uint32 i = 0; i < kNumberTextures; i++)
    textures_[i] = new Texture(renderer_, kTextures[i].path, kTextures[i].rows,
                               kTextures[i].columns);

  // Create the fonts
  fonts_[BIG_FONT] = new Font(renderer_, kFontsdirectories[REGULAR], 72);
  fonts_[MEDIUM_FONT] = new Font(renderer_, kFontsdirectories[REGULAR], 40);

  // Create the game manager and insert states
  gameManager_ = new GameManager(this);
  states_.insert(
      std::pair<States, State *>(States::GAME, new GameState(this, renderer_)));
  states_.insert(
      std::pair<States, State *>(States::MENU, new MenuState(this, renderer_)));
  states_.insert(std::pair<States, State *>(
      States::SCOREBOARD, new ScoreBoardState(this, renderer_)));
}

/// Public
// Destructor
Game::~Game() {
  for (auto state : states_) {
    delete state.second;
  }

  for (Uint32 i = 0; i < kNumberTextures; i++) {
    delete textures_[i];
  }
  delete fonts_[BIG_FONT];
  delete fonts_[MEDIUM_FONT];
  delete gameManager_;
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  TTF_Quit();
  SDL_Quit();
}

/// Public
// Get this game's textures
Texture **Game::getTextures() { return textures_; }

/// Public
// Get this game's fonts
Font **Game::getFonts() { return fonts_; }

/// Public
// Run the game's event loop
void Game::run() {
  // While it's not gameover (set when exit), run the event loop
  while (state_ != GAMEOVER) {
    State *cur = states_[state_];
    cur->init();
    cur->run();
  }
}

States Game::getState() { return state_; }

GameState *Game::getGameState() {
  return dynamic_cast<GameState *>(states_[GAME]);
}

/// Public
// Change the current state
void Game::changeState(const States &state) {
  state_ = state;
  State::current_->end();
}

/// Public
// Gets the game's game manager
GameManager *Game::getGameManager() { return gameManager_; }

/// Public
// Gets the game's world
b2World *Game::getWorld() { return world_; }

/// Public
// Sets this game's world
void Game::setWorld(b2World &world) { world_ = &world; }
