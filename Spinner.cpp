#include "Spinner.h"

Spinner::Spinner(uint16_t ledCount,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds)
: Visualization(ledCount, 1, hue, saturation, leds)
{
  this->ledCount = ledCount;
  this->length = 8;
  this->interval = 40;
}

void Spinner::display (unsigned long currentTime) {
  if (currentTime > this->nextTime) {
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
