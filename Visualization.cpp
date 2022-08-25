#include "Visualization.h"

Visualization::Visualization(uint16_t columns,
  uint16_t rows,
  uint8_t hue,
  uint8_t saturation,
  CRGB * leds,
  uint8_t cycle) {
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
  this->setCycle(cycle);
  this->cycleOffset = 0;
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

uint8_t Visualization::getValue() {
  return this->value;
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

void Visualization::setHalf() {
  CRGB c = CHSV(this->hue, this->saturation, this->value);
  for (uint16_t y=0; y<this->rows; y++) {
    for (uint16_t x=0; x<this->columns; x+=2) {
      uint16_t pos = this->xy2Pos(x, y);
      this->leds[pos] = c;
    }
  }
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

void Visualization::setCycle(uint8_t cycle) {
  this->cycle = cycle;
  this->cyclems = pow(this->cycle / 4, 2);
}

void Visualization::synchronize(uint32_t currentTime, uint32_t sync) {
  uint32_t cycleSync = this->sync +
  ((currentTime - this->lastSyncTime) * this->driftRatio);

  uint32_t lastCycleOffset = this->cycleOffset;

  this->lastSync = this->sync;

  // don't calculate drift on the first loop
  float lastDriftRatio =
    (float)(sync - this->lastSync) / (float)(currentTime - this->lastSyncTime);

  if (this->sync == 0) {
    // don't do anything on the first pass
  } else if (this->sync != 0 && this->driftRatio == 1.0) {
    // second pass, just set the drift
    this->driftRatio = lastDriftRatio;
  } else if (abs((int)cycleSync - (int)sync) > 10000) {
    this->driftRatio = 1.0;
  } else {
    // use a moving average
    this->driftRatio = (this->driftRatio * 0.9) + (lastDriftRatio * 0.1);
  }

  this->sync = sync;

  // Serial.print(this->lastSyncTime);
  // Serial.print("\t");
  // Serial.print(this->lastSync);
  // Serial.print("\t");
  // Serial.print(currentTime);
  // Serial.print("\t");
  // Serial.print(this->sync);
  // Serial.print("\t");
  // Serial.print((int)currentTime - (int)this->lastSyncTime);
  // Serial.print("\t");
  // Serial.print((int)this->sync - (int)this->lastSync);
  // Serial.print("\t");
  // Serial.print(this->driftRatio);
  // Serial.print("\t");
  // Serial.print(cycleSync);
  // Serial.print("\t");
  // Serial.print((int)cycleSync - (int)sync);
  // Serial.println();

  this->lastSyncTime = currentTime;
}

void Visualization::cycleLoop(uint32_t currentTime) {
  uint32_t cycleSync = this->sync +
    ((currentTime - this->lastSyncTime) * this->driftRatio);

  if (this->cycle > 0) {
    this->setHue((cycleSync / this->cyclems) % 256);
  }

  // if (currentTime > lastLog + 3000) {
  //   Serial.print(currentTime);
  //   Serial.print("\t");
  //   Serial.print(this->cycle);
  //   Serial.print("\t");
  //   Serial.print(this->cyclems);
  //   Serial.print("\t");
  //   Serial.print(this->sync);
  //   Serial.print("\t");
  //   Serial.print(cycleSync);
  //   Serial.print("\t");
  //   Serial.print(this->hue);
  //   Serial.println();
  //   lastLog = currentTime;
  // }
}
