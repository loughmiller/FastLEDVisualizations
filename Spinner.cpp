#include "Spinner.h"

Spinner::Spinner (uint8_t ledCount, CRGB * leds, CRGB color)
: Visualization(1, ledCount, leds, color)
{
  this->length = 12;
  this->interval = 40;
  this->color.maximizeBrightness();
}

void Spinner::inititalize() {
  Visualization::inititalize();
}

void Spinner::display (unsigned long currentTime) {
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
  for (uint8_t i=0; i<this->length; i++) {
    if ((y - i >= 0) && (y - i < this->rows)) {
      pos = this->xy2Pos(this->column, y - i);
      this->leds[pos] = this->color;
      this->leds[pos].fadeLightBy((256 / this->length) * i);
    }
  }
}
