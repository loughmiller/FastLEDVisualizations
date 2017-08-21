#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Sparkle : public Visualization {
  private :
    uint16_t emptyness;

  public :
    Sparkle(uint16_t columns,
      uint16_t rows,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds,
      uint16_t emptyness);

    void display();
};
