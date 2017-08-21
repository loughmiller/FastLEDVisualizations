#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class RainbowDrop : public Visualization {
  private :
    uint8_t rowStep;
    uint8_t columnStep;
    bool lastBeat;
    bool lastBeat2;

  public :
    RainbowDrop(uint8_t columns, uint8_t rows, uint8_t saturation, CRGB * leds);
    void display(unsigned long int currentTime, float intensity);
};
