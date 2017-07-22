#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <Arduino.h>
#include "FastLED.h"

class Visualization {
  protected :
    uint16_t columns;
    uint16_t rows;
    CRGB * leds;
    uint16_t frame;
    unsigned long nextTime;
    uint16_t interval;
    CRGB color;

  public :
    Visualization (uint16_t columns, uint16_t rows, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);

    uint16_t xy2Pos (uint16_t x, uint16_t y);

    void setColor (CRGB color);
};

#endif /* VISUALIZATION_H */
