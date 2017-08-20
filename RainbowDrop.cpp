#include "RainbowDrop.h"

RainbowDrop::RainbowDrop (uint16_t columns, uint16_t rows, CRGB * leds)
: Visualization(columns, rows, leds, 0x000000)
{
  this->rowStep = (int)(255.0 / (float)this->rows);
  this->columnStep = (int)(255.0 / (float)this->columns);
  this->lastBeat = false;
  this->lastBeat2 = false;
  this->inititalize();
  this->nextTime = millis();
}

void RainbowDrop::display (unsigned long currentTime, float intensity) {
  bool beat = false;
  if (intensity > 0.8) {
    beat = true;
  }

  int currentFrame = this->frame % 255;

  if (currentTime > this->nextTime) {
    // Serial.print(this->id);
    // Serial.print(": ");
    // Serial.print(currentTime);
    // Serial.print(" - ");
    // Serial.print(beat);
    // Serial.print(" - ");
    // Serial.println(this->lastBeat);

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

    this->nextTime += this->interval;
  }

  uint8_t timeOffset = 255 - currentFrame;

  // Serial.println("start");
  for (uint8_t y=0; y<this->rows; y++) {
    uint8_t rowOffset = this->rowStep * y;
    // Serial.println(hue);
    for (uint8_t x=0; x<this->columns; x++) {
      // uint8_t columnOffset = this->columnStep * x;
      uint8_t hue = timeOffset + rowOffset;
      CHSV c(hue, 234, 255);
      leds[xy2Pos(x, y)] = c;
    }
  }
  // Serial.println("end");
  // delay(1000);
}
