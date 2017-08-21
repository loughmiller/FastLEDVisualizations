#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Ladder : public Visualization {
  public :
    Ladder(uint8_t columns,
      uint8_t rows,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds);

    void inititalize();
    void display(unsigned long currentTime);
};
