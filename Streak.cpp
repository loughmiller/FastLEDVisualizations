#include "Streak.h"

Streak::Streak(uint16_t columns,
  uint16_t rows,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds)
: Visualization(columns, rows, hue, saturation, leds)
{
  this->length = 0;
  this->minLength = 8;
  this->maxLength = 16;
  this->minInterval = 0;
  this->maxInterval = 90;
  this->randomHue = false;
  this->fade = true;
  this->startTime = 0;
}

void Streak::inititalize(unsigned long currentTime) {
  // Serial.print("inititalize - ");
  // Serial.println(this->frame);
  this->frame = 0;
  this->startTime = currentTime;
  this->interval = random8(this->minInterval, this->maxInterval);
  this->column = random8(this->columns);
  this->length = random8(this->minLength, this->maxLength);
  if (this->randomHue) {
    this->setHue(random(256));
  }
}

void Streak::display (unsigned long currentTime) {
  this->frame = (currentTime - this->startTime)/this->interval;

  if (this->frame > (this->rows + this->length)) {
    this->inititalize(currentTime);
  }

  int y = this->frame;
  int pos;
  for (uint8_t i=0; i<this->length; i++) {
    if ((y - i >= 0) && (y - i < this->rows)) {
      // this->setLEDColorXY(this->column, y - i);
      pos = this->xy2Pos(this->column, y - i);
      this->leds[pos] = CHSV(this->hue, this->saturation, this->value);

      if (this->fade) {
        this->leds[pos].fadeLightBy((256 / this->length) * i);
      }
    }
  }
}

void Streak::setLengthMinMax(uint8_t min, uint8_t max) {
  this->minLength = min;
  this->maxLength = max;
}

void Streak::setIntervalMinMax(uint8_t min, uint8_t max) {
  this->minInterval = min;
  this->maxInterval = max;
}

void Streak::setFade(bool on) {
  this->fade = on;
}

void Streak::setRandomHue(bool on) {
  this->randomHue = on;
}
