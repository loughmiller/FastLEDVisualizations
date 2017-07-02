#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Ladder : public Visualization {
  private :
    int column;
    int length;
    CRGB color;

  public :
    Ladder (int columns, int rows, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);
};
