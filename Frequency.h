#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Frequency : public Visualization {
  private :
    int column;
    int length;
    CRGB color;
    int emptyness;

  public :
    Frequency (int columns, int rows, CRGB * leds, CRGB color);

    void display(unsigned long currentTime, int * levels);
};
