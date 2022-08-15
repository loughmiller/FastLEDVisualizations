#include "Sparkle.h"

Sparkle::Sparkle (uint16_t ledCount,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds,
  uint32_t emptiness)
: Visualization(ledCount, 1, hue, saturation, leds) {
    this->emptiness = emptiness;
}

void Sparkle::display (uint32_t currentTime) {
  this->driftLoop(currentTime);
  uint32_t i = random(this->emptiness);
  while (i < this->rows*this->columns) {
    this->setLEDColor(i);
    i = i + random(this->emptiness);
  }
}

void Sparkle::setEmptiness(uint32_t emptiness) {
  this->emptiness = emptiness;
}