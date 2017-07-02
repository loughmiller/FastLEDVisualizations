#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <Arduino.h>
#include "FastLED.h"

class Visualization {
  protected :
    int columns;
    int rows;
    CRGB * leds;
    int frame;
    unsigned long nextTime;
    int interval;

  public :
    Visualization (int columns, int rows, CRGB * leds);

    void inititalize();

    void display (unsigned long currentTime);

    int xy2Pos (int x, int y);
};

#endif /* VISUALIZATION_H */
