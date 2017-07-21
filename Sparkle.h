#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Sparkle : public Visualization {
  private :
    CRGB color;
    uint16_t emptyness;

  public :
    Sparkle (uint16_t columns, uint16_t rows, CRGB * leds, CRGB color, uint16_t emptyness);

    void inititalize();

    void display();
};
