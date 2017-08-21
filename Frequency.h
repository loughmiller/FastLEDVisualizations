#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Frequency : public Visualization {
  private :
    CRGB color;

  public :
    Frequency(uint8_t columns,
      uint8_t rows,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds);

    void display(unsigned long currentTime, uint8_t * levels);
};
