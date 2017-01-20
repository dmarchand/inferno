#include <Arduboy.h>
#include "inferno_bitmaps.h"
#include "config.h"
#include "wall.h"
#include "collision.h"



// Arduboy ref
Arduboy arduboy;

// Player variables
int pX = pStartX;
int pY = pStartY;

// What game mode we're in
int gameState = INTRO;


void setup() {
  arduboy.begin();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(framerate);
  intro();
}

void intro()
{
  if (DEBUG) {
    gameState = GAMEPLAY;
    return;
  }

  for (int i = -8; i < 28; i = i + 2)
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

  gameState = GAMEPLAY;

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

// Iterate through all walls so we can draw
void drawWalls() {
  for (int i = 0; i < numStoredWalls; i++) {
    drawWall(walls[i]);
  }
}

// Draw a specific wall
void drawWall(Wall wall) {
  for (int i = 0; i < wallSize; i++) {
    if (wall.blocks[i]) {
      int x = wall.x;
      int y = i * blockSize;
      drawBlock(x, y);
    }
  }
}

// Draw a wall block
void drawBlock(int x, int y) {
  arduboy.drawSlowXYBitmap(x, y, box, 8, 8, 1);
}

void endGame() {
  gameState = GAMEOVER;
}

void checkPlayerCollision() {
  int playerX = pX - (pWidth / 2);
  int playerXEnd = pX + (pWidth / 2);
  int playerY = pY - (pHeight / 2);
  int playerYEnd = pY + (pHeight / 2);

  for (int i = 0; i < numStoredWalls; i++) {
    if (!walls[i].disabled) {
      for (int q = 0; q < wallSize; q++) {
        if (walls[i].blocks[q]) {
          int blockX = walls[i].x;
          int blockXEnd = blockX + blockSize;
          int blockY = q * blockSize;
          int blockYEnd = blockY + blockSize;

          if (doRectanglesCollide(playerX, playerY, playerXEnd, playerYEnd,
                                  blockX, blockY, blockXEnd, blockYEnd)) {
            endGame();
            return;
          }
        }
      }
    }
  }
}

void doGameplay() {
  handleInput();
  updateWalls();
  drawPlayer();
  drawWalls();
  checkPlayerCollision();
}

void doGameOver() {
  resetGame();
  gameState = GAMEPLAY;
}

void resetGame() {
  pX = pStartX;
  pY = pStartY;
  initializeWalls();
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  // Is this too expensive?
  arduboy.clear();

  switch (gameState) {
    case GAMEPLAY:
      doGameplay();
      break;
    case GAMEOVER:
      doGameOver();
      break;
    default:
      break;
  }





  arduboy.display();

}
