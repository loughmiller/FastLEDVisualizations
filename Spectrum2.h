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
    uint_fast32_t drift;
    float totalMagnitudeMovingAverage;
    float lowPassPeakMovingAverage;
    float lowPassTroughMovingAverage;
    float lowPassMovingAverage;
    uint_fast32_t loggingTimestamp = 0;
    bool fill;
    void displayRow(uint8_t y, CRGB color);
    uint8_t lowPassCount = 4;

  public :
    Spectrum2(uint16_t columns,
      uint16_t rows,
      uint16_t rowOffset,
      uint16_t length,
      uint8_t hue,
      uint8_t saturation,
      bool invert,
      bool fill,
      CRGB * leds,
      uint8_t drift = 64);
    void display(float * intensity);
    float getDensity();
    void setDensity(float density);
    float getMagnitude();
};
