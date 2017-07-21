#include "Sparkle.h"

Sparkle::Sparkle (uint16_t columns, uint16_t rows, CRGB * leds, CRGB color, uint16_t emptyness)
: Visualization(columns, rows, leds)
{
  this->emptyness = emptyness;
  this->color = color;
  this->color.maximizeBrightness();
}

void Sparkle::display () {
  uint16_t i = random(this->emptyness);
  while (i < this->rows*this->columns) {
    Serial.print(this->rows);
    Serial.print(' ');
    Serial.print(this->columns);
    Serial.print(' ');
    Serial.println(i);
    this->leds[i] = this->color;
    i = i + random(this->emptyness);
  }
}
