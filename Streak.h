#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"

class Streak : public Visualization {
  private :
    uint8_t column;
    uint8_t length;
    uint8_t minLength;
    uint8_t maxLength;
    uint16_t minInterval;
    uint16_t maxInterval;
    bool fade;

  public :
    Streak (uint8_t columns, uint8_t rows, CRGB * leds, CRGB color);

    void inititalize();

    void display (unsigned long currentTime);

    void setLengthMinMax(uint8_t min, uint8_t max);

    void setIntervalMinMax(uint8_t min, uint8_t max);

    void setFade(bool on);
};
