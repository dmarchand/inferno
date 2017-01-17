
// Basic wall object
struct Wall
{
  int x;
  bool isFlashing;
  int flashTimeRemaining;
  bool blocks[wallSize];
};

// Wall variables
Wall walls[storedWalls] = { NULL };
int currentWallIndex = 0;
float timeToNextWall = wallSpawnDelay;


void updateWalls() {
  for(int i = 0; i < storedWalls; i++) {
    Wall wall = walls[i];
    
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
}

void checkWallBounds() {
  
}
