#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Frequency : public Visualization {
  private :
    CRGB color;

  public :
    Frequency (uint8_t columns, uint8_t rows, CRGB * leds, CRGB color);

    void display(unsigned long currentTime, uint8_t * levels);
};
