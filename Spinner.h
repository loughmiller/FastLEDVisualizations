#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Spinner : public Visualization {
  private :
    uint8_t ledCount;
    uint8_t length;

  public :
    Spinner (uint8_t ledCount, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);
};
