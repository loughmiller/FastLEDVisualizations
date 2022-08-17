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
  this->setDrift(drift);
  this->driftOffset = 0;
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

void Visualization::setAll() {
  this->setAllCRGB(CHSV(this->hue, this->saturation, this->value));
}

void Visualization::clearAll() {
  this->setAllCRGB(0x000000);
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
  uint32_t newDriftOffset = abs(driftOffset - millis());

  // Serial.print(millis());
  // Serial.print("\t");
  // Serial.print(this->driftOffset);
  // Serial.print("\t");
  // Serial.print(newDriftOffset);
  // Serial.print("\t");
  // Serial.print((int)newDriftOffset - (int)this->driftOffset);
  // Serial.println();

  this->driftOffset = newDriftOffset;

}

void Visualization::driftLoop(uint32_t currentTime) {
  uint32_t driftSync = this->driftOffset + currentTime;

  if (this->drift > 0) {
    this->setHue((driftSync / this->driftms) % 256);
  }

  // if (currentTime > lastLog + 5000) {
  //   Serial.print(currentTime);
  //   Serial.print("\t");
  //   Serial.print(this->drift);
  //   Serial.print("\t");
  //   Serial.print(this->driftms);
  //   Serial.print("\t");
  //   Serial.print(this->driftOffset);
  //   Serial.print("\t");
  //   Serial.print(driftSync);
  //   Serial.print("\t");
  //   Serial.print(this->hue);
  //   Serial.println();
  //   lastLog = currentTime;
  // }
}
