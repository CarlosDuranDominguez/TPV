#pragma once

#include <Box2D/Box2D.h>

typedef unsigned int uint;
class ArkanoidSettings
{
private:
  static float32 _windowHeight;
  static float32 _windowWidth;

public:
  // Methods
  static float32 getWindowHeight();
  static float32 getWindowWidth();
  static void setSceneDimensions();
  static void setWindowWidth(float32 width);
  static void setUp(float32 width, float32 height);
  static void setWindowHeight(float32 height);
  // General
  const static float32 framerate;
  const static float32 widthRatio;
  const static float32 heightRatio;
  const static int initialLives;
  const static uint totalLevels;
  static b2Vec2 sceneUpperLeftCorner;
  static float32 sceneWidth;
  static float32 sceneHeight;
  // Ball
  const static float32 ballAngle;
  const static float32 ballRadiusRatio;
  const static float32 ballSpeedRatio;
  static float32 ballRadius;
  static float32 ballSpeed;
  // Block
  const static float32 blockHeightRatio;
  const static float32 blockWidthRatio;
  static float32 blockHeight;
  static float32 blockWidth;
  // Enemy
  const static float32 enemyRadiusRatio;
  const static float32 enemySpeedRatio;
  static float32 enemyRadius;
  static float32 enemySpeed;
  // Paddle
  const static float32 paddleSpeedRatio;
  const static float32 paddleWidthRatio;
  const static float32 paddleHeightRatio;
  const static float32 paddleMinimumWidthRatio;
  const static float32 paddleMaximumWidthRatio;
  static float32 paddleSpeed;
  static float32 paddleWidth;
  static float32 paddleHeight;
  static float32 paddleMinimumWidth;
  static float32 paddleMaximumWidth;
  // Reward
  const static uint rewardFramerate;
  const static float32 rewardWidthRatio;
  const static float32 rewardHeigthRatio;
  const static float32 rewardSpeedRatio;
  static float32 rewardWidth;
  static float32 rewardHeigth;
  static float32 rewardSpeed;
  // Wall
  const static float32 wallWidthRatio;
  const static float32 wallHeightRatio;
  static float32 wallWidth;
  static float32 wallHeight;
};
