#ifndef WALL_H
#define WALL_H

// Basic wall object
struct Wall
{
  int x; // Where the wall is positioned on the screen
  bool isPreparing; // Whether or not the wall is actively moving or warning the player
  int prepareTimeRemaining; // How long until the wall activates
  bool blocks[wallSize]; // Each 8x8 square of the wall, and whether or not it exists or is empty
  int moveSpeed; // How fast this wall moves towards the left
  bool disabled; // If this wall shouldn't be interacted with
};

// Wall variables
Wall walls[numStoredWalls]; // Used to keep track of our walls in memory
int currentWallIndex = 0; // Which wall index to write to when we create a new one
int currentWallSpeed = wallBaseSpeed; // How fast walls move on the current difficulty level
float timeToNextWall = wallSpawnDelay; // How long until we spawn the next wall

// Since we're allocating the Wall struct on the stack
// we can't delete them, as they'll exist until we exit the local block,
// which in this case is our execution context. Instead lets just pool them
void initializeWalls() {
  for(int i = 0; i < numStoredWalls; i++) {
      Wall newWall = 
      {
        wallSpawnX,
        false,
        wallBaseActivateDelay,
        { false },
        currentWallSpeed,
        true
      };

      walls[i] = newWall;
   }
}

// Checks each wall in 'walls' and decides how to deal with it
void updateWalls() {
  for(int i = 0; i < numStoredWalls; i++) {
    if(walls[i].isPreparing) {
      
    }
    else if(!walls[i].disabled) {
      walls[i].x -= walls[i].moveSpeed;
    }
  }
}

// Initializes a new 'Wall' struct with a random gap
void spawnWall() {
  int gapStart = 3; // Randomly decide where the gap starts
  int gapEnd = gapStart + wallGapSize;

  // Get a wall from the pool
  Wall newWall = walls[currentWallIndex];

  newWall.x = wallSpawnX;
  newWall.disabled = false;
  
  // Fill in the blocks array, making sure to include the gap
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

  // Loop back around in the wall tracking array
  if(currentWallIndex > numStoredWalls) {
    currentWallIndex = 0;
  }
}

#endif
