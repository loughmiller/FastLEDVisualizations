#include "SoundReaction.h"

SoundReaction::SoundReaction(uint16_t start, uint16_t end, CRGB * leds, CRGB onColor, CRGB offColor)
: Visualization(0, 0, leds, onColor)
{
  this->start = start;
  this->end = end;
  this->onColor = onColor;
  this->offColor = offColor;
}

void SoundReaction::display(float intensity) {
  CRGB onColor = this->onColor;
  if (intensity > 0.85) {
    intensity = (intensity - 0.5) / 0.5;
    onColor.fadeLightBy((1-(intensity)) * 256);
    for (int i=this->start; i<this->end; i++) {
      leds[i] = onColor;
    }
  } else {
    for (int i=this->start; i<this->end; i++) {
      leds[i] = this->offColor;
    }
  }
}

void SoundReaction::setOnColor(CRGB color) {
  this->onColor = color;
}

void SoundReaction::setOffColor(CRGB color) {
  this->offColor = color.fadeLightBy(244);
}
