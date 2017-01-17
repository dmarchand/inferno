#ifndef WALL_H
#define WALL_H

// Basic wall object
struct Wall
{
  int x;
  bool isFlashing;
  int flashTimeRemaining;
  bool blocks[wallSize];
};

// Wall variables
Wall walls[numStoredWalls] = { NULL };
int currentWallIndex = 0;
int currentWallSpeed = wallBaseSpeed;
float timeToNextWall = wallSpawnDelay;


void updateWalls() {
  for(int i = 0; i < numStoredWalls; i++) {
    if(walls[i].isFlashing) {
      
    }
    else {
      walls[i].x -= currentWallSpeed;
    }
  }
}

void spawnWall() {
  int gapStart = 3;
  int gapEnd = gapStart + wallGapSize;
  
  Wall newWall = 
  {
    wallSpawnX,
    false,
    wallBaseActivateDelay,
    { false }
  };

  
  for(int i = 0; i < wallSize; i++) {
    if(i >= gapStart && i < gapEnd) {
      newWall.blocks[i] = false;
    }
    else {
      newWall.blocks[i] = true;
    }
  }

  walls[currentWallIndex] = newWall;
  currentWallIndex++;
  
  if(currentWallIndex > numStoredWalls) {
    currentWallIndex = 0;
  }
}

#endif
