#ifndef CONFIG_H
#define CONFIG_H

// Debug mode makes some things quicker
const bool DEBUG = true;

// Core game config
const int framerate = 30;

// Player config
const int pSpeed = 2;
const int pStartX = 5;
const int pStartY = 32;
const int pMinX = 2;
const int pMaxX = 120;
const int pMinY = 2;
const int pMaxY = 55;
const int pWidth = 4;
const int pHeight = 4;

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
const int wallSpawnDelay = 50; 

#endif
