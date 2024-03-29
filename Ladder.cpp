#include "Ladder.h"

#define MIN_INTERVAL 2

Ladder::Ladder(uint8_t columns,
  uint8_t rows,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds)
: Visualization(columns, rows, hue, saturation, leds) {
}

void Ladder::inititalize() {
  this->interval = random16(256, 512);;
}

void Ladder::display (unsigned long currentTime) {
  uint16_t currentFrame = this->frame % this->rows;

  if (currentFrame == 0) {
    this->inititalize();
  }

  if (currentTime > this->nextTime) {
    // Serial.print(this->id);
    // Serial.print(": ");
    // Serial.println(currentTime);
    this->frame++;
    this->nextTime = currentTime + this->interval;
    this->interval = max(int(this->interval * 0.96), MIN_INTERVAL);
  }

  uint8_t y = this->rows - (currentFrame + 1);

  if (y < 0) {
    for (uint8_t i=0; i<this->rows * this->columns; i++) {
      this->leds[i] = color;
    }
  } else {
    for (uint8_t i=0; i<this->columns; i++) {
      this->leds[xy2Pos(i, y)] = this->color;
    }
  }
}
