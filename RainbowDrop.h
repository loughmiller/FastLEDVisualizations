#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class RainbowDrop : public Visualization {
  private :
    uint8_t interval;
    uint8_t rowStep;
    uint8_t columnStep;
    bool lastBeat;
    bool lastBeat2;

  public :
    RainbowDrop (uint16_t columns, uint16_t rows, CRGB * leds);
    void display(unsigned long int currentTime, float intensity);
};
