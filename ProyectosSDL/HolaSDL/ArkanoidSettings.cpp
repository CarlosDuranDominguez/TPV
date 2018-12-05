#include "ArkanoidSettings.h"

// Methods
float32 ArkanoidSettings::getWindowHeight()
{
  return _windowHeight;
};

float32 ArkanoidSettings::getWindowWidth()
{
  return _windowWidth;
};

void ArkanoidSettings::setSceneDimensions()
{
  if (widthRatio / heightRatio > _windowWidth / _windowHeight)
  {
    sceneWidth = _windowWidth;
    sceneHeight = _windowWidth * heightRatio / widthRatio;
  }
  else
  {
    sceneHeight = _windowHeight;
    sceneWidth = _windowHeight * widthRatio / heightRatio;
  }
  float32 ratio = sceneWidth / widthRatio;
  sceneUpperLeftCorner = b2Vec2{(_windowWidth - sceneWidth) / 2.0f, (_windowHeight - sceneHeight) / 2.0f};
  ballRadius = ratio * ballRadiusRatio;
  ballSpeed = ratio * ballSpeedRatio;
  blockHeight = ratio * blockHeightRatio;
  blockWidth = ratio * blockWidthRatio;
  enemyRadius = ratio * enemyRadiusRatio;
  enemySpeed = ratio * enemySpeedRatio;
  paddleSpeed = ratio * paddleSpeedRatio;
  paddleWidth = ratio * paddleWidthRatio;
  paddleHeight = ratio * paddleHeightRatio;
  paddleMaximumWidth = ratio * paddleMaximumWidthRatio;
  paddleMinimumWidth = ratio * paddleMinimumWidthRatio;
  rewardWidth = ratio * rewardWidthRatio;
  rewardHeigth = ratio * rewardHeigthRatio;
  rewardSpeed = ratio * rewardSpeedRatio;
  wallWidth = ratio * wallWidthRatio;
  wallHeight = ratio * wallHeightRatio;
};

void ArkanoidSettings::setWindowWidth(float32 width)
{
  _windowWidth = width;
  setSceneDimensions();
};

void ArkanoidSettings::setUp(float32 width, float32 height)
{
  _windowWidth = width;
  _windowHeight = height;
  setSceneDimensions();
};

void ArkanoidSettings::setWindowHeight(float32 height)
{
  _windowHeight = height;
  setSceneDimensions();
};

// General
float32 ArkanoidSettings::_windowHeight = 0.0f;
float32 ArkanoidSettings::_windowWidth = 0.0f;
const float32 ArkanoidSettings::framerate = 120.0f;
const float32 ArkanoidSettings::widthRatio = 1400.0f;
const float32 ArkanoidSettings::heightRatio = 2000.0f;
const int ArkanoidSettings::initialLives = 3;
const uint ArkanoidSettings::totalLevels = 3;
b2Vec2 ArkanoidSettings::sceneUpperLeftCorner = b2Vec2{0.f, 0.f};
float32 ArkanoidSettings::sceneWidth = 0.0f;
float32 ArkanoidSettings::sceneHeight = 0.0f;
// Ball
const float32 ArkanoidSettings::ballAngle = b2_pi / 4.0f;
const float32 ArkanoidSettings::ballRadiusRatio = 17.5f;
const float32 ArkanoidSettings::ballSpeedRatio = 1000.0f;
float32 ArkanoidSettings::ballRadius = 0.0f;
float32 ArkanoidSettings::ballSpeed = 0.0f;
// Block
const float32 ArkanoidSettings::blockHeightRatio = 40.0f;
const float32 ArkanoidSettings::blockWidthRatio = 100.0f;
float32 ArkanoidSettings::blockHeight = 0.0f;
float32 ArkanoidSettings::blockWidth = 0.0f;
// Enemy
const float32 ArkanoidSettings::enemyRadiusRatio = 20.0f;
const float32 ArkanoidSettings::enemySpeedRatio = 600.0f;
float32 ArkanoidSettings::enemyRadius = 0.0f;
float32 ArkanoidSettings::enemySpeed = 0.0f;
// Paddle
const float32 ArkanoidSettings::paddleSpeedRatio = 1200.0f;
const float32 ArkanoidSettings::paddleWidthRatio = 200.0f;
const float32 ArkanoidSettings::paddleHeightRatio = 40.0f;
const float32 ArkanoidSettings::paddleMinimumWidthRatio = 150.0f;
const float32 ArkanoidSettings::paddleMaximumWidthRatio = 250.0f;
float32 ArkanoidSettings::paddleSpeed = 0.0f;
float32 ArkanoidSettings::paddleWidth = 0.0f;
float32 ArkanoidSettings::paddleHeight = 0.0f;
float32 ArkanoidSettings::paddleMinimumWidth = 0.0f;
float32 ArkanoidSettings::paddleMaximumWidth = 0.0f;
// Reward
const float32 ArkanoidSettings::rewardFramerate = 15.0f;
const float32 ArkanoidSettings::rewardWidthRatio = 100.0f;
const float32 ArkanoidSettings::rewardHeigthRatio = 40.0f;
const float32 ArkanoidSettings::rewardSpeedRatio = 700.0f;
float32 ArkanoidSettings::rewardWidth = 0.0f;
float32 ArkanoidSettings::rewardHeigth = 0.0f;
float32 ArkanoidSettings::rewardSpeed = 0.0f;
// Wall
const float32 ArkanoidSettings::wallWidthRatio = 50.0f;
const float32 ArkanoidSettings::wallHeightRatio = 1400.0f;
float32 ArkanoidSettings::wallWidth = 0.0f;
float32 ArkanoidSettings::wallHeight = 0.0f;
