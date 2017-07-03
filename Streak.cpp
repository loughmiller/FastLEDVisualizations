#include "Streak.h"

Streak::Streak (uint8_t columns, uint8_t rows, CRGB * leds, CRGB color)
: Visualization(columns, rows, leds)
{
  this->length = 0;
  this->color = color;
  this->color.maximizeBrightness();
  this->minLength = 8;
  this->maxLength = 16;
  this->minInterval = 0;
  this->maxInterval = 90;
}

void Streak::inititalize() {
  Visualization::inititalize();
  this->interval = random8(this->minInterval, this->maxInterval);
  this->column = random8(this->columns);
  this->length = random8(this->minLength, this->maxLength);
}

void Streak::display (unsigned long currentTime) {
  int currentFrame = this->frame % (this->rows + this->length);

  if (currentFrame == 0) {
    this->inititalize();
  }

  if (currentTime > this->nextTime) {
    // Serial.print(this->id);
    // Serial.print(": ");
    // Serial.println(currentTime);
    this->frame++;
    this->nextTime = currentTime + this->interval;
  }

  int y = currentFrame;
  int pos;
  for (int i=0; i<this->length; i++) {
    if ((y - i >= 0) && (y - i < this->rows)) {
      pos = this->xy2Pos(this->column, y - i);
      this->leds[pos] = this->color;
      this->leds[pos].fadeToBlackBy((256 / this->length) * i);
    }
  }
}

void Streak::setColor(CRGB color) {
  this->color = color;
  // this->color.maximizeBrightness();
}

void Streak::setLengthMinMax(uint8_t min, uint8_t max) {
  this->minLength = min;
  this->maxLength = max;
}

void Streak::setIntervalMinMax(uint8_t min, uint8_t max) {
  this->minInterval = min;
  this->maxInterval = max;
}
