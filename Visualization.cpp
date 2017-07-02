#include "Visualization.h"

Visualization::Visualization (int columns, int rows, CRGB * leds) {
  this->columns = columns;
  this->rows = rows;
  this->leds = leds;
  this->frame = 0;
  this->interval = 20;
}

void Visualization::inititalize() {
  this->frame = 0;
  this->nextTime = 0;
}

int Visualization::xy2Pos (int x, int y) {
  int pos = x * this->rows;
  if (x % 2 == 0) {
    pos = pos + y;
  } else {
    pos = pos + ((this->rows - 1) - y);
  }

  return pos;
}
