#include "Sparkle.h"

Sparkle::Sparkle (uint8_t columns, uint8_t rows, CRGB * leds, CRGB color, uint16_t emptyness)
: Visualization(columns, rows, leds)
{
  this->emptyness = emptyness;
  this->color = color;
  this->color.maximizeBrightness();
}

void Sparkle::display () {
  uint16_t i = random(this->emptyness);
  while (i < this->rows*this->columns) {
    this->leds[i] = this->color;
    i = i + random(this->emptyness);
  }
}
