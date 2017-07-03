#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <Arduino.h>
#include "FastLED.h"

class Visualization {
  protected :
    uint8_t columns;
    uint8_t rows;
    CRGB * leds;
    uint16_t frame;
    unsigned long nextTime;
    uint16_t interval;

  public :
    Visualization (uint8_t columns, uint8_t rows, CRGB * leds);

    void inititalize();

    void display (unsigned long currentTime);

    uint16_t xy2Pos (uint8_t x, uint8_t y);
};

#endif /* VISUALIZATION_H */
