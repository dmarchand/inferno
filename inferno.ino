#include <Arduboy.h>
#include "inferno_bitmaps.h"
#include "config.h"
#include "wall.h"



// Arduboy ref
Arduboy arduboy;

// Player variables
int pX = pStartX;
int pY = pStartY;

// Wall variables
Wall walls[storedWalls] = { NULL };
int currentWallIndex = 0;
float timeToNextWall = wallSpawnDelay;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(framerate);
    intro();
}

void intro()
{
  if(DEBUG) {
    return;
  }
  
  for(int i = -8; i < 28; i = i + 2)
  {
    arduboy.clear();
    arduboy.setCursor(30, i);
    arduboy.print("Dan's Games");
    arduboy.display();
  }

  arduboy.tunes.tone(987, 160);
  delay(160);
  arduboy.tunes.tone(1318, 400);
  delay(2000);

  arduboy.clear();
}

// Deal with player button presses
void handleInput() {
  if (arduboy.pressed(RIGHT_BUTTON) && pX <= pMaxX) {
    pX += pSpeed;
  }
  else if (arduboy.pressed(LEFT_BUTTON) && pX >= pMinX) {
    pX -= pSpeed;
  }

  if (arduboy.pressed(UP_BUTTON) && pY >= pMinY) {
    pY -= pSpeed;
  }
  else if (arduboy.pressed(DOWN_BUTTON) && pY <= pMaxY) {
    pY += pSpeed;
  }
}

// Render player sprite
void drawPlayer() {
  arduboy.drawSlowXYBitmap(pX, pY, player, 5, 5, 1);
}

void drawBlock(int x, int y) {
  arduboy.drawSlowXYBitmap(x, y, box, 8, 8, 1);
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

void drawWalls() {
  for(int i = 0; i < storedWalls; i++) {
    //if(walls[i] != NULL) {
      drawWall(walls[i]);
    //}
  }
}

void drawWall(Wall wall) {
  for(int i = 0; i < wallSize; i++) {
    if(wall.blocks[i]) {
      int x = wall.x;
      int y = i * blockSize;
      drawBlock(x, y);
    }
  }
}

void loop() {
    if (!(arduboy.nextFrame()))
    return;

    // Is this too expensive?
    arduboy.clear();

    handleInput();
    drawPlayer();
    drawWalls();

    if(DEBUG && currentWallIndex == 0) {
      spawnWall();
    }

    arduboy.display();
    
}
