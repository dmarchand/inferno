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
  bool scoreCounted; // If the wall has already incremented player score
};

// Wall variables
Wall walls[numStoredWalls]; // Used to keep track of our walls in memory
int currentWallIndex = 0; // Which wall index to write to when we create a new one
int currentWallSpeed = wallBaseSpeed; // How fast walls move on the current difficulty level
int wallSpawnDelay = baseWallSpawnDelay; // Set base wall spawn delay
int timeToNextWall = wallSpawnDelay; // How long until we spawn the next wall

// Since we're allocating the Wall struct on the stack
// we can't delete them, as they'll exist until we exit the local block,
// which in this case is our execution context. Instead lets just pool them
void initializeWalls() {
  for(int i = 0; i < numStoredWalls; i++) {
      Wall newWall = 
      {
        -999,
        false,
        wallBaseActivateDelay,
        { false },
        currentWallSpeed,
        true,
        true
      };

      walls[i] = newWall;
   }

   // Re-init wall-specific stuff
   currentWallIndex = 0;
   currentWallSpeed = wallBaseSpeed;
   wallSpawnDelay = baseWallSpawnDelay;
   timeToNextWall = wallSpawnDelay;
}

// Initializes a new 'Wall' struct with a random gap
void spawnWall(int difficulty) {
  int computedWallGapSize = wallGapSize;
  if(difficulty >= difficultyTighterGapsThreshold && random(0, 2) == 0) {
    computedWallGapSize--;
  }
  
  int gapStart = random(0, wallSize - computedWallGapSize + 1); // Randomly decide where the gap starts
  int gapEnd = gapStart + computedWallGapSize;

  // Get a wall from the pool
  Wall newWall = walls[currentWallIndex];

  // Set up the parameters for the wall we just pulled out of the pool
  newWall.x = wallSpawnX;
  newWall.disabled = false;
  newWall.moveSpeed = currentWallSpeed;
  newWall.scoreCounted = false;
  Serial.println("Wall created");
  
  // Fill in the blocks array, making sure to include the gap
  for(int i = 0; i < wallSize; i++) {
    if(i >= gapStart && i < gapEnd) {
      newWall.blocks[i] = false;
    }
    else {
      newWall.blocks[i] = true;
    }
  }

  Serial.println("Blocks initialized");

  // Return our wall to the pool
  walls[currentWallIndex] = newWall;

  currentWallIndex++;

  // Loop back around in the wall tracking array
  if(currentWallIndex >= numStoredWalls) {
    currentWallIndex = 0;
  }
}

// Checks each wall in 'walls' and decides how to deal with it
void updateWalls(int difficulty) {
  for(int i = 0; i < numStoredWalls; i++) {
    if(walls[i].isPreparing) {
      
    }
    else if(!walls[i].disabled) {
      walls[i].x -= walls[i].moveSpeed;
    }
  }

  // Count down and spawn a wall if needed
  if(timeToNextWall <= 0) {
    spawnWall(difficulty);
    timeToNextWall = wallSpawnDelay;
  }
  else {
    timeToNextWall--;
  }
  
}

#endif
