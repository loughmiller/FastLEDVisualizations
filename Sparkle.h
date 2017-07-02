#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Sparkle : public Visualization {
  private :
    int column;
    int length;
    CRGB color;
    int emptyness;

  public :
    Sparkle (int columns, int rows, CRGB * leds, CRGB color, int emptyness);

    void inititalize();

    void display ();
};
