#include "Visualization.h"

Visualization::Visualization (uint16_t columns, uint16_t rows, CRGB * leds, CRGB color) {
  this->columns = columns;
  this->rows = rows;
  this->leds = leds;
  this->color = color;
  this->frame = 0;
  this->interval = 20;
}

void Visualization::inititalize() {
  this->frame = 0;
  this->nextTime = 0;
}

uint16_t Visualization::xy2Pos (uint16_t x, uint16_t y) {
  uint16_t pos = x * this->rows;
  if (x % 2 == 0) {
    pos = pos + y;
  } else {
    pos = pos + ((this->rows - 1) - y);
  }

  return pos;
}

void Visualization::setColor(CRGB color) {
  this->color = color;
  // this->color.maximizeBrightness();
}

void Visualization::setInterval(uint16_t interval) {
  this->interval = interval;
}
