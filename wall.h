
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
    Wall* wall = &walls[i];

    if(wall->isFlashing) {
      
    }
    else {
      wall->x -= currentWallSpeed;
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

