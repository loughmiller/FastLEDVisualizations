#include "Pulse.h"

Pulse::Pulse(uint16_t offset, uint16_t count, CRGB * leds, CRGB color)
: Visualization(0, 0, leds)
{
  this->offset = offset;
  this->count = count;
  this->color = color;
  this->color.maximizeBrightness();
  this->interval = 10;
  this->nextTime = 0;
}

void Pulse::display (unsigned long currentTime) {
  int currentFrame = this->frame % 200;

  if (currentTime > this->nextTime) {
    // Serial.print(this->id);
    // Serial.print(": ");
    // Serial.println(abs(currentFrame-64));
    this->frame++;
    this->nextTime = currentTime + this->interval;
    // FastLED.setBrightness(abs(currentFrame - 72)+8);
  }

  for (uint16_t i=this->offset; i<this->offset+this->count; i++) {
    leds[i] = this->color;
    leds[i].fadeLightBy(abs(currentFrame - 100));
  }
}
