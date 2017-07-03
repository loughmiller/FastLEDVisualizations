#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Ladder : public Visualization {
  private :
    CRGB color;

  public :
    Ladder (uint8_t columns, uint8_t rows, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);
};
