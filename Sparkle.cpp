#include "Sparkle.h"

Sparkle::Sparkle (uint16_t ledCount,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds,
  uint16_t emptyness)
: Visualization(ledCount, 1, hue, saturation, leds)
{
  this->emptyness = emptyness;
}

void Sparkle::display () {
  uint16_t i = random(this->emptyness);
  while (i < this->rows*this->columns) {
    this->setLEDColor(i);
    i = i + random(this->emptyness);
  }
}
