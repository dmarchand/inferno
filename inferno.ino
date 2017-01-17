#include <Arduboy.h>
Arduboy arduboy;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(30);

    intro();
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
}

void loop() {
    if (!(arduboy.nextFrame()))
    return;

    arduboy.display();
}
