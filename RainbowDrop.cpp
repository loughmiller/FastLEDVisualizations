#include "RainbowDrop.h"

RainbowDrop::RainbowDrop(uint8_t columns, uint8_t rows, uint8_t saturation, CRGB * leds)
: Visualization(columns, rows, 0, saturation, leds)
{
  this->rowStep = (int)(255.0 / (float)this->rows);
  this->columnStep = (int)(255.0 / (float)this->columns);
  this->lastBeat = false;
  this->lastBeat2 = false;
  this->nextTime = millis();
}

void RainbowDrop::display (unsigned long currentTime, float intensity) {
  bool beat = false;
  if (intensity > 0.8) {
    beat = true;
  }

  int currentFrame = this->frame % 255;

  if (currentTime > this->nextTime) {
    // Serial.print(currentTime);
    // Serial.print(" - ");
    // Serial.print(this->interval);
    // Serial.print(" - ");
    // Serial.println(this->nextTime);

    this->lastBeat2 = this->lastBeat;

    if (!beat) {
      this->lastBeat = false;
    }

    if (beat && !this->lastBeat && !this->lastBeat2) {
      this->frame += rowStep;
      this->lastBeat = true;
    } else {
      this->frame++;
    }

    this->nextTime = currentTime + this->interval;
  }

  uint8_t timeOffset = 255 - currentFrame;

  // Serial.println("start");
  for (uint8_t y=0; y<this->rows; y++) {
    uint8_t rowOffset = this->rowStep * y;
    // Serial.println(hue);
    for (uint8_t x=0; x<this->columns; x++) {
      // uint8_t columnOffset = this->columnStep * x;
      uint8_t hue = timeOffset + rowOffset;
      CHSV c(hue, this->saturation, 255);
      leds[xy2Pos(x, y)] = c;
    }
  }
  // Serial.println("end");
  // delay(1000);
}
