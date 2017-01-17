#include <Arduboy.h>
#include "inferno_bitmaps.h"

// Arduboy ref
Arduboy arduboy;

// Player variables
int pX = 3;
int pY = 10;
int pSpeed = 2;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(30);

    //intro();
}

void intro()
{
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
  if (arduboy.pressed(RIGHT_BUTTON)) {
    pX += pSpeed;
  }
  else if (arduboy.pressed(LEFT_BUTTON)) {
    pX -= pSpeed;
  }

  if (arduboy.pressed(UP_BUTTON)) {
    pY -= pSpeed;
  }
  else if (arduboy.pressed(DOWN_BUTTON)) {
    pY += pSpeed;
  }
}

// Render player sprite
void drawPlayer() {
  arduboy.drawSlowXYBitmap(pX, pY, ball, 5, 5, 1);
}

void loop() {
    if (!(arduboy.nextFrame()))
    return;

    // Is this too expensive?
    arduboy.clear();

    handleInput();
    drawPlayer();

    arduboy.display();
    
}
