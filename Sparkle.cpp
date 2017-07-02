#include "Sparkle.h"

Sparkle::Sparkle (int columns, int rows, CRGB * leds, CRGB color, int emptyness)
: Visualization(columns, rows, leds)
{
  this->emptyness = emptyness;
  this->color = color;
  this->color.maximizeBrightness();
}

void Sparkle::display () {
  int i = random(this->emptyness);
  while (i < this->rows*this->columns) {
    this->leds[i] = this->color;
    i = i + random(this->emptyness);
  }
}
