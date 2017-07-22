#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Pulse : public Visualization {
  private :
    int offset;
    int count;
    int column;
    int length;
    int interval;

  public :
    Pulse(uint16_t offset, uint16_t count, CRGB * leds, CRGB color);

    void inititalize();

    void display(unsigned long currentTime);
};
