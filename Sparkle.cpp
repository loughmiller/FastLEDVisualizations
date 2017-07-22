#include "Sparkle.h"

Sparkle::Sparkle (uint16_t columns, uint16_t rows, CRGB * leds, CRGB color, uint16_t emptyness)
: Visualization(columns, rows, leds, color)
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
