#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Streak : public Visualization {
  private :
    int column;
    int length;
    CRGB color;

  public :
    Streak (int columns, int rows, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);

    void setColor (CRGB color);
};
