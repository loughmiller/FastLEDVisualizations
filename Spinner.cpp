#include "Spinner.h"

Spinner::Spinner (uint8_t ledCount, CRGB * leds, CRGB color)
: Visualization(1, ledCount, leds, color)
{
  this->ledCount = ledCount;
  this->length = 10;
  this->interval = 45;
  this->color.maximizeBrightness();
}

void Spinner::inititalize() {
  Visualization::inititalize();
}

void Spinner::display (unsigned long currentTime) {
  if (this->frame == 0) {
    this->inititalize();
  }

  if (currentTime > this->nextTime) {
    // Serial.print(this->id);
    // Serial.print(": ");
    // Serial.println(currentTime);
    this->frame++;
    this->nextTime = currentTime + this->interval;
  }

  for (uint8_t i=0; i<this->length; i++) {
    if ((this->frame - i) > 0) {
      int pos = (this->frame - i) % this->ledCount;
      this->leds[pos] = this->color;
      this->leds[pos].fadeLightBy((256 / this->length) * i);
    }
  }
}
