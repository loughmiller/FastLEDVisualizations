#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Sparkle : public Visualization {
  private :
    CRGB color;
    uint16_t emptyness;

  public :
    Sparkle (uint8_t columns, uint8_t rows, CRGB * leds, CRGB color, uint16_t emptyness);

    void inititalize();

    void display();
};
