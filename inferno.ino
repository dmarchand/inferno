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

// Score tracking
int score = 0;

// Current difficulty level
int difficulty = 0;


void setup() {
  arduboy.begin();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(framerate);

  if (DEBUG) {
    Serial.begin(9600);
  }

  resetGame();
  intro();
}

void intro()
{
  if (DEBUG) {
    score = 0;
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
  arduboy.drawSlowXYBitmap(pX, pY, player, 8, 8, 1);
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

// This behemoth is responsible for determining if
// the player collided with something it shouldn't.
void checkPlayerCollision() {
  // Before we do anything, calculate player collision bounds
  int playerX = pX - (pWidth / 2);
  int playerXEnd = pX + (pWidth / 2);
  int playerY = pY - (pHeight / 2);
  int playerYEnd = pY + (pHeight / 2);

  // Iterate through each wall to start collision checking
  for (int i = 0; i < numStoredWalls; i++) {
    if (!walls[i].disabled) { // If the wall is disabled let's save some CPU cycles
      for (int q = 0; q < wallSize; q++) { // If the wall is enabled, iterate through its blocks
        // Much like before, we calculate the bounding box for...the box
        int blockX = walls[i].x;
        int blockXEnd = blockX + blockSize;
        int blockY = q * blockSize;
        int blockYEnd = blockY + blockSize;

        // Finall, let's see if the player collides with the box!
        if (doRectanglesCollide(playerX, playerY, playerXEnd, playerYEnd,
                                blockX, blockY, blockXEnd, blockYEnd)) {
          if (walls[i].blocks[q]) {
            endGame(); // If the player collides, we can end the game and bail out of this nested loop early
            return;
          }
          else if (!walls[i].scoreCounted) {
            // We collided with an empty block, which means we get a point!
            score++;
            Serial.println("Score++");
            walls[i].scoreCounted = true;
          }
        }
      }
    }
  }
}

// Display the player score
void drawScore() {
  arduboy.setCursor(scoreDisplayX, scoreDisplayY); // Shift the cursor over
  arduboy.print(score);
}

// Display the difficulty level
void drawDifficulty() {
  int displayDifficulty = difficulty + 1;

  arduboy.setCursor(difficultyDisplayX, difficultyDisplayY); // Shift the cursor
  arduboy.print("Lv:");
  arduboy.setCursor(difficultyDisplayX + 12, difficultyDisplayY);
  arduboy.print(displayDifficulty);
}

// Called every loop if we're in gameplay mode
// Handles everything you'd expect!
void doGameplay() {
  handleInput();
  updateWalls(difficulty);
  drawPlayer();
  drawWalls();
  drawScore();
  drawDifficulty();
  checkDifficulty();
  checkPlayerCollision();
}

// Called if we're in game over mode
// Displays game over screen, final score, etc
void doGameOver() {
  resetGame();
  score = 0;
  gameState = GAMEPLAY;
}

// Clear game state so we can start anew!
void resetGame() {
  pX = pStartX;
  pY = pStartY;
  difficulty = 0;
  initializeWalls();
}

void checkDifficulty() {
  if (difficulty >= sizeof(difficultyThresholds) / sizeof(difficultyThresholds[0])) {
    return;
  }

  int threshold = difficultyThresholds[difficulty];
  if (score >= threshold) {
    difficulty++;
    currentWallSpeed += wallSpeedGain;
    wallSpawnDelay -= wallSpawnDelayReduction;
  }
}

void loop() {
  // If the arduboy isn't ready to render the next frame, chill
  if (!(arduboy.nextFrame()))
    return;

  // Wipe the screen
  arduboy.clear();

  // Check game state and act accordingly
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

  // Finally, let's render the screen
  arduboy.display();

}
