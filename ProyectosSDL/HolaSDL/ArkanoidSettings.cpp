#include "ArkanoidSettings.h"

// Get the window's height
float32 ArkanoidSettings::getWindowHeight() { return windowHeight_; };

// Get the window's width
float32 ArkanoidSettings::getWindowWidth() { return windowWidth_; };

// Set the scene's dimensions
void ArkanoidSettings::setSceneDimensions() {
  if (widthRatio_ / heightRatio_ > windowWidth_ / windowHeight_) {
    sceneWidth_ = windowWidth_;
    sceneHeight_ = windowWidth_ * heightRatio_ / widthRatio_;
  } else {
    sceneHeight_ = windowHeight_;
    sceneWidth_ = windowHeight_ * widthRatio_ / heightRatio_;
  }
  const auto ratio = sceneWidth_ / widthRatio_;
  sceneUpperLeftCorner_ = b2Vec2{(windowWidth_ - sceneWidth_) / 2.0f,
                                 (windowHeight_ - sceneHeight_) / 2.0f};
  ballRadius_ = ratio * ballRadiusRatio_;
  ballSpeed_ = ratio * ballSpeedRatio_;
  blockHeight_ = ratio * blockHeightRatio_;
  blockWidth_ = ratio * blockWidthRatio_;
  enemyRadius_ = ratio * enemyRadiusRatio_;
  enemySpeed_ = ratio * enemySpeedRatio_;
  paddleSpeed_ = ratio * paddleSpeedRatio_;
  paddleWidth_ = ratio * paddleWidthRatio_;
  paddleHeight_ = ratio * paddleHeightRatio_;
  paddleMaximumWidth_ = ratio * paddleMaximumWidthRatio_;
  paddleMinimumWidth_ = ratio * paddleMinimumWidthRatio_;
  rewardWidth_ = ratio * rewardWidthRatio_;
  rewardHeight_ = ratio * rewardHeightRatio_;
  rewardSpeed_ = ratio * rewardSpeedRatio_;
  wallWidth_ = ratio * wallWidthRatio_;
  wallHeight_ = ratio * wallHeightRatio_;
};

// Setup the scene dimensions
void ArkanoidSettings::setUp(const float32 width, const float32 height) {
  windowWidth_ = width;
  windowHeight_ = height;
  setSceneDimensions();
};

// Set the window's width
void ArkanoidSettings::setWindowWidth(const float32 width) {
  windowWidth_ = width;
  setSceneDimensions();
};

// Set the window's height
void ArkanoidSettings::setWindowHeight(const float32 height) {
  windowHeight_ = height;
  setSceneDimensions();
};

// General
float32 ArkanoidSettings::windowHeight_ = 0.0f;
float32 ArkanoidSettings::windowWidth_ = 0.0f;
const float32 ArkanoidSettings::framerate_ = 120.0f;
const float32 ArkanoidSettings::widthRatio_ = 1200.0f;
const float32 ArkanoidSettings::heightRatio_ = 2000.0f;
const int ArkanoidSettings::initialLives_ = 3;
const Uint32 ArkanoidSettings::totalLevels_ = 3;
b2Vec2 ArkanoidSettings::sceneUpperLeftCorner_ = b2Vec2{0.f, 0.f};
float32 ArkanoidSettings::sceneWidth_ = 0.0f;
float32 ArkanoidSettings::sceneHeight_ = 0.0f;

// Ball
const float32 ArkanoidSettings::ballAngle_ = b2_pi / 4.0f;
const float32 ArkanoidSettings::ballRadiusRatio_ = 17.5f;
const float32 ArkanoidSettings::ballSpeedRatio_ = 1000.0f;
float32 ArkanoidSettings::ballRadius_ = 0.0f;
float32 ArkanoidSettings::ballSpeed_ = 0.0f;

// Block
const float32 ArkanoidSettings::blockHeightRatio_ = 40.0f;
const float32 ArkanoidSettings::blockWidthRatio_ = 100.0f;
float32 ArkanoidSettings::blockHeight_ = 0.0f;
float32 ArkanoidSettings::blockWidth_ = 0.0f;

// Enemy
const float32 ArkanoidSettings::enemyRadiusRatio_ = 20.0f;
const float32 ArkanoidSettings::enemySpeedRatio_ = 600.0f;
float32 ArkanoidSettings::enemyRadius_ = 0.0f;
float32 ArkanoidSettings::enemySpeed_ = 0.0f;

// Paddle
const float32 ArkanoidSettings::paddleSpeedRatio_ = 1200.0f;
const float32 ArkanoidSettings::paddleWidthRatio_ = 200.0f;
const float32 ArkanoidSettings::paddleHeightRatio_ = 40.0f;
const float32 ArkanoidSettings::paddleMinimumWidthRatio_ = 150.0f;
const float32 ArkanoidSettings::paddleMaximumWidthRatio_ = 250.0f;
float32 ArkanoidSettings::paddleSpeed_ = 0.0f;
float32 ArkanoidSettings::paddleWidth_ = 0.0f;
float32 ArkanoidSettings::paddleHeight_ = 0.0f;
float32 ArkanoidSettings::paddleMinimumWidth_ = 0.0f;
float32 ArkanoidSettings::paddleMaximumWidth_ = 0.0f;

// Reward
const Uint32 ArkanoidSettings::rewardFramerate_ = 15;
const float32 ArkanoidSettings::rewardWidthRatio_ = 100.0f;
const float32 ArkanoidSettings::rewardHeightRatio_ = 40.0f;
const float32 ArkanoidSettings::rewardSpeedRatio_ = 700.0f;
float32 ArkanoidSettings::rewardWidth_ = 0.0f;
float32 ArkanoidSettings::rewardHeight_ = 0.0f;
float32 ArkanoidSettings::rewardSpeed_ = 0.0f;

// Wall
const float32 ArkanoidSettings::wallWidthRatio_ = 50.0f;
const float32 ArkanoidSettings::wallHeightRatio_ = 1400.0f;
float32 ArkanoidSettings::wallWidth_ = 0.0f;
float32 ArkanoidSettings::wallHeight_ = 0.0f;
