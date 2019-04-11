#pragma once
#include <Box2D/Box2D.h>
#include "SDL.h"

class ArkanoidSettings {
  static float32 windowHeight_;
  static float32 windowWidth_;

 public:
  // Methods
  static float32 getWindowHeight();
  static float32 getWindowWidth();
  static void setSceneDimensions();
  static void setWindowWidth(float32 width);
  static void setUp(float32 width, float32 height);
  static void setWindowHeight(float32 height);
  // General
  const static float32 framerate_;
  const static float32 widthRatio_;
  const static float32 heightRatio_;
  const static int initialLives_;
  const static Uint32 totalLevels_;
  static b2Vec2 sceneUpperLeftCorner_;
  static float32 sceneWidth_;
  static float32 sceneHeight_;
  // Ball
  const static float32 ballAngle_;
  const static float32 ballRadiusRatio_;
  const static float32 ballSpeedRatio_;
  static float32 ballRadius_;
  static float32 ballSpeed_;
  // Block
  const static float32 blockHeightRatio_;
  const static float32 blockWidthRatio_;
  static float32 blockHeight_;
  static float32 blockWidth_;
  // Enemy
  const static float32 enemyRadiusRatio_;
  const static float32 enemySpeedRatio_;
  static float32 enemyRadius_;
  static float32 enemySpeed_;
  // Paddle
  const static float32 paddleSpeedRatio_;
  const static float32 paddleWidthRatio_;
  const static float32 paddleHeightRatio_;
  const static float32 paddleMinimumWidthRatio_;
  const static float32 paddleMaximumWidthRatio_;
  static float32 paddleSpeed_;
  static float32 paddleWidth_;
  static float32 paddleHeight_;
  static float32 paddleMinimumWidth_;
  static float32 paddleMaximumWidth_;
  // Reward
  const static Uint32 rewardFramerate_;
  const static float32 rewardWidthRatio_;
  const static float32 rewardHeightRatio_;
  const static float32 rewardSpeedRatio_;
  static float32 rewardWidth_;
  static float32 rewardHeight_;
  static float32 rewardSpeed_;
  // Wall
  const static float32 wallWidthRatio_;
  const static float32 wallHeightRatio_;
  static float32 wallWidth_;
  static float32 wallHeight_;
};
