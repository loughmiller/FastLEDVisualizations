#include "SoundReaction.h"

SoundReaction::SoundReaction(uint16_t start,
  uint16_t end,
  uint8_t onHue,
  uint8_t offHue,
  uint8_t saturation,
  CRGB * leds)
: Visualization(0, 0, onHue, saturation, leds)
{
  this->start = start;
  this->end = end;
  this->onHue = onHue;
  this->offHue = offHue;
}

void SoundReaction::display(float intensity) {
  CRGB onColor = this->color;
  if (intensity > 0.85) {
    intensity = (intensity - 0.5) / 0.5;
    onColor.fadeLightBy((1-(intensity)) * 256);
    for (int i=this->start; i<this->end; i++) {
      this->leds[i] = onColor;
    }
  } else {
    CRGB offColor = CHSV(this->offHue, this->saturation, 80);
    for (int i=this->start; i<this->end; i++) {
      this->leds[i] = offColor;
    }
  }
}

void SoundReaction::setOnHue(uint8_t hue) {
  this->setHue(hue);
}

void SoundReaction::setOffHue(uint8_t hue) {
  this->offHue = hue;
}
