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
    uint32_t startTime;
    bool fade;
    bool randomHue;

  public :
    Streak(uint16_t columns,
      uint16_t rows,
      uint8_t hue,
      uint8_t saturation,
      CRGB * leds);

    void inititalize(unsigned long currentTime);
    void display(unsigned long currentTime);
    void setLengthMinMax(uint8_t min, uint8_t max);
    void setIntervalMinMax(uint8_t min, uint8_t max);
    void setFade(bool on);
    void setRandomHue(bool on);
};
