#include "Visualization.h"

Visualization::Visualization(uint16_t columns,
  uint16_t rows,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds,
  uint8_t drift) {
  this->columns = columns;
  this->rows = rows;
  this->leds = leds;
  this->hue = hue;
  this->saturation = saturation;
  this->frame = 0;
  this->nextTime = 0;
  this->interval = 20;
  this->value = 255;

  this->color = CHSV(hue, saturation, 255);
}

void Visualization::setLEDColorXY(uint16_t x, uint16_t y) {
  this->setLEDColor(xy2Pos(x, y));
}

void Visualization::setLEDColor(uint16_t pos) {
  this->leds[pos] = this->color;
}

uint16_t Visualization::xy2Pos(uint16_t x, uint16_t y) {
  uint16_t pos = x * this->rows;
  pos = pos + y;

  // if (x % 2 == 0) {
  //   pos = pos + y;
  // } else {
  //   pos = pos + ((this->rows - 1) - y);
  // }

  return pos;
}

void Visualization::setHue(uint8_t hue) {
  this->hue = hue;
  this->color = CHSV(this->hue, this->saturation, this->value);
}

uint8_t Visualization::getHue() {
  return this->hue;
}

void Visualization::setSaturation(uint8_t saturation) {
  this->saturation = saturation;
  this->color = CHSV(this->hue, this->saturation, this->value);
}

void Visualization::setValue(uint8_t value) {
  this->value = value;
  this->color = CHSV(this->hue, this->saturation, this->value);
}

void Visualization::setInterval(uint16_t interval) {
  this->interval = interval;
}

void Visualization::setAllHue(uint8_t hue) {
  this->setAllCRGB(CHSV(hue, this->saturation, this->value));
}

void Visualization::setAllCRGB(CRGB c) {
  for (uint16_t y=0; y<this->rows; y++) {
    for (uint16_t x=0; x<this->columns; x++) {
      uint16_t pos = this->xy2Pos(x, y);
      this->leds[pos] = c;
    }
  }
}

void Visualization::setDrift(uint8_t drift) {
  this->drift = drift;
  this->driftms = pow(this->drift / 4, 2);
}

void Visualization::setDriftOffset(uint32_t driftOffset) {
  this->driftOffset = driftOffset;
}

void Visualization::driftLoop(uint32_t currentTime) {
  uint32_t driftSync = abs(this->driftOffset - currentTime);
  if (this->drift > 0) {
    this->hue = (driftSync / this->driftms) % 256;
  }
}
