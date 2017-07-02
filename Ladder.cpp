#include "Ladder.h"

#define MIN_INTERVAL 2

Ladder::Ladder (int columns, int rows, CRGB * leds, CRGB color)
: Visualization(columns, rows, leds)
{
  this->color = color;
}

void Ladder::inititalize() {
  Visualization::inititalize();
  this->interval = random16(256, 512);;
}

void Ladder::display (unsigned long currentTime) {
  int currentFrame = this->frame % this->rows;

  if (currentFrame == 0) {
    this->inititalize();
  }

  if (currentTime > this->nextTime) {
    // Serial.print(this->id);
    // Serial.print(": ");
    // Serial.println(currentTime);
    this->frame++;
    this->nextTime = currentTime + this->interval;
    this->interval = max(this->interval * 0.96, MIN_INTERVAL);
  }

  int y = this->rows - (currentFrame + 1);

  if (y < 0) {
    for (int i=0; i<this->rows * this->columns; i++) {
      this->leds[i] = color;
    }
  } else {
    for (int i=0; i<this->columns; i++) {
      this->leds[xy2Pos(i, y)] = this->color;
    }
  }
}
