#ifndef CONFIG_H
#define CONFIG_H

#define INTRO 0
#define STARTSCREEN 1
#define GAMEPLAY 2
#define GAMEOVER 3

// Debug mode makes some things quicker
const bool DEBUG = true;

// Core game config
const int framerate = 30;

// GUI config
const int scoreDisplayX = 110;
const int scoreDisplayY = 2;
const int difficultyDisplayX = 5;
const int difficultyDisplayY = 2;

// Player config
const int pSpeed = 3;
const int pStartX = 5;
const int pStartY = 32;
const int pMinX = 2;
const int pMaxX = 120;
const int pMinY = 2;
const int pMaxY = 55;
const int pWidth = 3;
const int pHeight = 3;

// Wall config
const float wallFlashInterval = 3;
const int wallSpawnX = 110;
const int wallGapSize = 3;
const int wallSize = 8;
const int blockSize = 8;
const int numStoredWalls = 8;
const int minX = -5;

// Gameplay tuning
const int wallBaseActivateDelay = 8;
const float wallActivateReduction = 0.1;
const int wallBaseSpeed = 2;
const float wallSpeedGain = 1;
const int baseWallSpawnDelay = 50; 
const int wallSpawnDelayReduction = 8;
const int difficultyThresholds[] = { 10, 20, 35, 50 };
const int difficultyTighterGapsThreshold = 3;

#endif
