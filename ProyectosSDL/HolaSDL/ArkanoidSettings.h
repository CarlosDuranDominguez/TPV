#pragma once

#include<Box2D/Box2D.h>

typedef unsigned int uint;
class ArkanoidSettings {
private:
	static uint _windowHeight;
	static uint _windowWidth;
public:
	//Methods
	static float32 getWindowHeight();
	static float32 getWindowWidth();
	static void setSceneDimensions();
	static void setWindowWidth(uint width);
	static void setUp(uint width, uint height);
	static void setWindowHeight(uint height);
	// General
	const static float32 framerate;
	const static float32 widthRatio;
	const static float32 heightRatio;
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
	static float32 paddleSpeed;
	static float32 paddleWidth;
	static float32 paddleHeight;
	//Reward 
	const static float32 rewardFramerate;
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