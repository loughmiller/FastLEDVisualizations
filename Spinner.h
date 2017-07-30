#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Spinner : public Visualization {
  private :
    uint8_t column;
    uint8_t length;
    uint8_t minLength;
    uint8_t maxLength;
    uint16_t minInterval;
    uint16_t maxInterval;

  public :
    Spinner (uint8_t ledCount, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);
};
