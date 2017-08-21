#include "Sparkle.h"

Sparkle::Sparkle (uint16_t columns,
  uint16_t rows,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds,
  uint16_t emptyness)
: Visualization(columns, rows, hue, saturation, leds)
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
