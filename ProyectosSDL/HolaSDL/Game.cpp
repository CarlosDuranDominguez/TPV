﻿#include "Game.h"
#include "ArkanoidSettings.h"
#include "GameState.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "SDLError.h"
#include "ScoreBoardState.h"

GameManager *Game::gameManager_ = nullptr;
b2World *Game::world_ = nullptr;
Game *Game::current_ = nullptr;

// Constructor
Game::Game() : states_(new GameStateMachine()) {
  // Set up the Arkanoid settings for the window's width and height
  ArkanoidSettings::setUp(kWinWidth, kWinHeight);
  current_ = this;

  // Initialize SDL and TTF
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw SDLError("Error initializing SDL");
  if (TTF_Init() < 0) throw SDLError("Error loading the SDL font");

  // Create the window and renderer
  window_ = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, kWinWidth, kWinHeight,
                             SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  // If window or renderer is a null pointer, throw a SDLError
  if (window_ == nullptr || renderer_ == nullptr)
    throw SDLError("Error loading the SDL window or renderer");

  // Create the textures
  for (Uint32 i = 0; i < kNumberTextures; i++)
    textures_[i] = new Texture(renderer_, kTextures[i].path, kTextures[i].rows,
                               kTextures[i].columns);

  // Create the fonts
  fonts_[BIG_FONT] = new Font(renderer_, kFontsdirectories[REGULAR], 72);
  fonts_[MEDIUM_FONT] = new Font(renderer_, kFontsdirectories[REGULAR], 40);

  // Create the game manager and insert states
  gameManager_ = new GameManager(this);
  states_->pushState(new MenuState(this, renderer_));
}

// Destructor
Game::~Game() {
  delete states_;
  for (auto &texture : textures_) {
    delete texture;
  }
  delete fonts_[BIG_FONT];
  delete fonts_[MEDIUM_FONT];
  delete gameManager_;
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  TTF_Quit();
  SDL_Quit();
}

// Get this game's textures
Texture **Game::getTextures() { return textures_; }

// Get this game's fonts
Font **Game::getFonts() { return fonts_; }

// Run the game's event loop
void Game::run() const {
  // Set the start time, run state's event loop
  b2Timer startTime;
  State *state;

  // The event loop follows this scheme:
  // → Create all pending-to-create game objects
  // → Handle SDL events (provided by SDL's event poll)
  // → Handle updates (updates all game objects of the game)
  // → Handle fixed updates (called every second)
  // → Handle after updates (called after the physics engine has run)
  // → Render all the game objects from the scene
  // → Run all the pending events of this tick from the stack
  // → Destroy all the elements that are pending to destroy
  while ((state = states_->currentState())) {
    State::current_ = state;
    if (!state->finished()) state->create();
    if (!state->finished()) state->handleEvents();
    if (!state->finished()) state->update();
    if (startTime.GetMilliseconds() / 1000.0f >=
        1.0f / ArkanoidSettings::framerate_) {
      if (!state->finished())
        state->fixUpdate(startTime.GetMilliseconds() / 1000.0f);
      startTime.Reset();
    }
    if (!state->finished()) state->afterUpdate();
    if (!state->finished()) state->render();
    if (!state->finished()) state->events();
    if (!state->finished()) state->destroy();
  }
}

GameState *Game::getGameState() const {
  return dynamic_cast<GameState *>(states_->currentState());
}

GameStateMachine *Game::getGameStateMachine() const { return states_; }

void Game::flushStates() const {
  while (!states_->empty()) {
    const auto state = states_->currentState();
    state->end();
    states_->popState();
  }
}

SDL_Renderer *Game::getRenderer() const { return renderer_; }

// Gets the game's game manager
GameManager *Game::getGameManager() { return gameManager_; }

// Gets the game's world
b2World *Game::getWorld() { return world_; }

// Sets this game's world
void Game::setWorld(b2World &world) { world_ = &world; }
