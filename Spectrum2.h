#include <Arduino.h>
#include <FastLED.h>
#include "Visualization.h"
#include <algorithm>    // std::sort

class Spectrum2 : public Visualization {
  private :
    uint16_t rowOffset;
    uint16_t length;
    bool invert;
    float density;
    float threshold;
    float peak;
    int16_t drift;
    float totalMagnitudeMovingAverage;
    uint_fast32_t loggingTimestamp = 0;

  public :
    Spectrum2(uint16_t columns,
      uint16_t rows,
      uint16_t rowOffset,
      uint16_t length,
      uint8_t hue,
      uint8_t saturation,
      bool invert,
      CRGB * leds);
    void display(float * intensity);
    void setDrift(uint8_t drift);
    float getDensity();
    void setDensity(float density);
    float getMagnitude();
};
