#include "Streak.h"

Streak::Streak (int columns, int rows, CRGB * leds, CRGB color)
: Visualization(columns, rows, leds)
{
  this->length = 0;
  this->color = color;
  this->color.maximizeBrightness();
}

void Streak::inititalize() {
  Visualization::inititalize();
  this->interval = random8(90);
  this->column = random8(this->columns);
  this->length = random8(8, 16);
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
