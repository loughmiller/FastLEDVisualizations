#include "Frequency.h"

Frequency::Frequency (int columns, int rows, CRGB * leds, CRGB color)
: Visualization(columns, rows, leds)
{
  this->interval = 1000;
  this->color = color;
  this->color.maximizeBrightness();
  this->nextTime = 0;
}

void Frequency::display(unsigned long currentTime, int * levels) {
  // FREQ_0
  for(int y=0; y<levels[0]/17; y++) {
    this->leds[this->xy2Pos(0, 15 - y)] = this->color;
    this->leds[this->xy2Pos(5, 15 - y)] = this->color;
  }

  // FREQ_1
  for(int y=0; y<levels[1]/17; y++) {
    this->leds[this->xy2Pos(1, 15 - y)] = this->color;
    this->leds[this->xy2Pos(6, 15 - y)] = this->color;
  }

  // FREQ_2
  for(int y=0; y<levels[2]/17; y++) {
    this->leds[this->xy2Pos(2, 15 - y)] = this->color;
    this->leds[this->xy2Pos(7, 15 - y)] = this->color;
  }

  // FREQ_3
  for(int y=0; y<levels[3]/17; y++) {
    this->leds[this->xy2Pos(3, 15 - y)] = this->color;
  }

  // FREQ_4
  for(int y=0; y<levels[4]/17; y++) {
    this->leds[this->xy2Pos(8, 15 - y)] = this->color;
  }

  // FREQ_5
  for(int y=0; y<levels[5]/17; y++) {
    this->leds[this->xy2Pos(4, 15 - y)] = this->color;
  }

  // FREQ_6
  for(int y=0; y<levels[6]/17; y++) {
    this->leds[this->xy2Pos(9, 15 - y)] = this->color;
  }
}
